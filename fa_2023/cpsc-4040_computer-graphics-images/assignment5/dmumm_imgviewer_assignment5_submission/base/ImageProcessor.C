#include "ImageProcessor.h"

using namespace image;

void ImageProcessor::applyBias(Pixel const bias, Image & imageToAlter)
{
	using RawImageValues = float *;
	RawImageValues pRawData = imageToAlter.getRawData();

	int const width = imageToAlter.getWidth();
	int const height = imageToAlter.getHeight();
	int const channelCount = imageToAlter.getChannelCount();

	for(int jRow = 0; jRow < height; jRow++)
	{
#pragma omp parallel for
		for(int iCol = 0; iCol < width; iCol++)
		{
			long index = (long)iCol + (long)width * (long)jRow;
			for(int channel = 0; channel < channelCount; channel++)
			{
				pRawData[channel + (long)channelCount * index] += bias[channel];
			}
		}
	}
}

void ImageProcessor::applyBrightness(float multiplier, Image & imageToAlter)
{
	using RawImageValues = float *;
	RawImageValues pRawData = imageToAlter.getRawData();

#pragma omp parallel for
	for(long elementIndex = 0; elementIndex < imageToAlter.getNumElements(); elementIndex++)
	{
		pRawData[elementIndex] = pRawData[elementIndex] * multiplier;
	}
}

void ImageProcessor::applyGamma(float gamma, Image & imageToAlter)
{

	int const SHIFT = 1;

	using RawImageValues = float *;
	RawImageValues pRawData = imageToAlter.getRawData();

	/* 	size_t nans = 0;
	    size_t infs = 0; */

#pragma omp parallel for
	for(long elementIndex = 0; elementIndex < imageToAlter.getNumElements(); elementIndex++)
	{

		float currentValue = pRawData[elementIndex];

		/* 		if(std::isnan(currentValue)) nans++;
				if(std::isinf(currentValue)) infs++; */

		float newValue = std::pow(currentValue + SHIFT, gamma);

		if(std::isnan(newValue)) continue;
		if(std::isinf(newValue)) continue;

		pRawData[elementIndex] = newValue - SHIFT;
	}
	/* 	std::cout << "NaNs: " << nans << "\n";
		std::cout << "Infs: " << infs << "\n"; */
}

void ImageProcessor::applyNormalizedGamma(float gamma, Image & imageToAlter)
{
	Image normalizedImage;
	Image output = imageToAlter;
	std::cout << "Applying contrast normalization..." << std::flush;
	ChannelNormalizationData values = applyContrastNormalization(imageToAlter, normalizedImage);
	std::cout << "done.\nApplying gamma transformation..." << std::flush;
	/*     applyGamma(gamma, normalizedImage);
	    std::cout << "done.\nReversing contrast normalization..." << std::flush;
	 */
	reverseContrastNormalization(values, normalizedImage, output);
	output = normalizedImage;
	std::cout << "done.\n";
}

void ImageProcessor::doBoundedLinearConvolution(Stencil const & stencil, Image const & input, Image & output)
{
	output.clear();
	output = input;

	int const halfWidth = stencil.getHalfwidth();
	int const channelCount = output.getChannelCount();
	int const height = output.getHeight();
	int const width = output.getWidth();

#pragma omp parallel for
	for(int imageRowIndex = 0; imageRowIndex < height; imageRowIndex++)
	{
		for(int pixelIndex = 0; pixelIndex < width; pixelIndex++)
		{
			Pixel outputPixel(channelCount, 0.0);
			Pixel sample(channelCount, 0.0);

			int bottomNeighbor = imageRowIndex - halfWidth;
			int topNeighbor = imageRowIndex + halfWidth;
			for(int neighborRow = bottomNeighbor; neighborRow <= topNeighbor; neighborRow++)
			{
				// Define stencil-space & image-space vertical indexes of current stencil row
				int stencilRow = neighborRow - imageRowIndex;
				int sampleRow = neighborRow;

				int leftmostNeighbor = pixelIndex - halfWidth;
				int rightmostNeighbor = pixelIndex + halfWidth;
				for(int neighborPixel = leftmostNeighbor; neighborPixel <= rightmostNeighbor; neighborPixel++)
				{
					// Define stencil-space & image-space horizontal indexes of current stencil column
					int stencilCol = neighborPixel - pixelIndex;
					int sampleCol = neighborPixel;

					// Retrieve stencil value at current stencil row and column
					float const & stencil_value = stencil(stencilCol, stencilRow);

					// If sample coordinates are outside of image bounds, set sample pixel to black
					// else, fill sample pixel with values from sample image

					if(sampleCol < 0 || sampleCol >= width
					|| sampleRow < 0 || sampleRow >= height)
					{
						std::fill(sample.begin(), sample.end(), 0.0f);
					} else
					{
						input.getValue(sampleCol, sampleRow, sample);
					}

					// Iterate through each channel of the pixel
					for(int channelIndex = 0; channelIndex < channelCount; channelIndex++)
					{
						// Apply weight to current channel of current pixel
						float weightedValue = sample[channelIndex] * stencil_value;

						// Increment value of current channel of current pixel by weighted value of given neighborhood pixel channel
						outputPixel[channelIndex] += weightedValue;
					}
				}
			}
			// Assign given pixel containing weighted sum of neighborhood to output image's equivalent pixel
			output.setValue(pixelIndex, imageRowIndex, outputPixel);
		}
	}
}

void ImageProcessor::doCircularLinearConvolution(Stencil const & stencil, Image const & input, Image & output)
{
	output.clear();
	output = input;

	int const halfWidth = stencil.getHalfwidth();

#pragma omp parallel for
	for(int imageRowIndex = 0; imageRowIndex < output.getHeight(); imageRowIndex++) {

		int bottomNeighbor = imageRowIndex - halfWidth;
		int topNeighbor = imageRowIndex + halfWidth;

		for(int pixelIndex = 0; pixelIndex < output.getWidth(); pixelIndex++) {

			int leftmostNeighbor = pixelIndex - halfWidth;
			int rightmostNeighbor = pixelIndex + halfWidth;

			Pixel outputPixel(output.getChannelCount(), 0.0);
			Pixel sample(input.getChannelCount(), 0.0);

			for(int neighborRow = bottomNeighbor; neighborRow <= topNeighbor; neighborRow++) {

				int stencilRow = neighborRow - imageRowIndex;
				int sampleRow = neighborRow;

				// Handle neighborhood values outside of vertical bounds

				if(sampleRow < 0) sampleRow += output.getHeight();
				if(sampleRow >= output.getHeight()) sampleRow -= output.getHeight();

				for(int neighborPixel = leftmostNeighbor; neighborPixel <= rightmostNeighbor; neighborPixel++)
				{
					int stencilCol = neighborPixel - pixelIndex;
					int sampleCol = neighborPixel;

					if(sampleCol < 0) sampleCol += output.getWidth();
					if(sampleCol >= output.getWidth()) sampleCol -= output.getWidth();

					float const & stencil_value = stencil(stencilCol, stencilRow);

					input.getValue(sampleCol, sampleRow, sample);

					for(int channelIndex = 0; channelIndex < sample.size(); channelIndex++)
					{
						float weightedValue = sample[channelIndex] * stencil_value;
						outputPixel[channelIndex] = outputPixel[channelIndex] + weightedValue;
					}
				}
			}

			output.setValue(pixelIndex, imageRowIndex, outputPixel);
		}
	}
}

ImageProcessor::ChannelNormalizationData ImageProcessor::applyContrastNormalization(Image const & input, Image & output)
{
	output.clear();
	output = input;

	int const channelCount = input.getChannelCount();
	int const height = input.getHeight();
	int const width = input.getWidth();

	Pixel const channelAverages = input.getChannelAverages();
	Pixel const channelRMSs = input.getChannelRMSs();

	Pixel inputPixelValue(channelCount, 0.0f);
	Pixel outputPixelValue(channelCount, 0.0f);

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			input.getValue(x, y, inputPixelValue);
			outputPixelValue = inputPixelValue;
			float differenceFromAverage = 0.0f;
			for(int channel = 0; channel < channelCount; channel++)
			{
				if(channelRMSs[channel] == 0) continue;

				differenceFromAverage = inputPixelValue[channel] - channelAverages[channel];
				outputPixelValue[channel] = differenceFromAverage / channelRMSs[channel];
			}
			// std::cout << "Contrast Transformation attempting at pixel (" << x << ", " << y << ")...\n";
			output.setValue(x, y, outputPixelValue);
			// std::cout << "Contrast Transformation applied at pixel (" << x << ", " << y << ")...\n";
		}
	}
	std::vector<Pixel> normalizationData;
	normalizationData.push_back(channelAverages);
	normalizationData.push_back(channelRMSs);

	output.setNormalizationData(normalizationData);

	return normalizationData;
}

void ImageProcessor::reverseContrastNormalization(ChannelNormalizationData const & normalizationData, Image const & normalizedImage, Image & output)
{
	assert(normalizationData.size() == 2 && "Normalization data must contain exactly two elements.");

	output.clear();
	output = normalizedImage;

	Pixel const & channelAverages = normalizationData[0];
	Pixel const & channelRMSs = normalizationData[1];

	int width = normalizedImage.getWidth();
	int height = normalizedImage.getHeight();
	int channelCount = normalizedImage.getChannelCount();

	Pixel pixelValue(channelCount, 0.0f);

	std::cout << "\n Via channel averages: {";
	for(int i = 0; i < channelAverages.size(); i++)
	{
		std::cout << channelAverages[i] << ", ";
	}
	std::cout << "} and channel RMSs: {";
	for(int i = 0; i < channelRMSs.size(); i++)
	{
		std::cout << channelRMSs[i] << ", ";
	}
	std::cout << "}\n"
		  << std::flush;

	// #pragma omp parallel for//TODO
	for(int jRow = 0; jRow < height; jRow++)
	{
		for(int iCol = 0; iCol < width; iCol++)
		{
			normalizedImage.getValue(iCol, jRow, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				if(channelRMSs[channel] == 0)
				{
					pixelValue[channel] = channelAverages[channel];
					continue;
				}
				pixelValue[channel] = (pixelValue[channel] * channelRMSs[channel]) + channelAverages[channel];
			}
			output.setValue(iCol, jRow, pixelValue);
		}
	}
}

void ImageProcessor::applyHistogramEqualization(int num_bins, Image const & input, Image & output)
{

	output.clear();
	output = input;

	int const channelCount = input.getChannelCount();
	int const height = input.getHeight();
	int const width = input.getWidth();
	int const pixelCount = width * height;

	HistogramArray histograms;
	NormalizedHistogramArray normalizedHistograms, CDFs;
	Pixel minValues, maxValues;
	Pixel pixelValue(channelCount, 0.0f);

	std::cout << "\tCalculating histograms...\n";
	input.calculateHistograms(histograms, minValues, maxValues, num_bins);
	std::cout << "\tNormalizing histograms...\n";
	input.normalizeHistograms(histograms, normalizedHistograms, pixelCount);
	std::cout << "\tCalculating CDFs...\n";
	input.computeCDFs(normalizedHistograms, CDFs);
	std::cout << "\tApplying CDFs...\n";
	// Apply CDF to remap pixel values
	for(int y = 0; y < height; y++)
	{
		/* 		std::cout << "\t\tProcessing row " << y << "...\n";
		 */
		for(int x = 0; x < width; x++)
		{
			/* 			std::cout << "\t\t\tProcessing pixel (" << x << ", " << y << ")...\n";
			 */
			input.getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				/* 				std::cout << "\t\t\t\tProcessing channel " << channel << "...\n";
								std::cout << "\t\t\t\t\tPixel value: " << pixelValue[channel] << "\n";
				 */
				if(maxValues[channel] == minValues[channel])
					continue;

				int binIndex = static_cast<int>((pixelValue[channel] - minValues[channel]) / (maxValues[channel] - minValues[channel]) * (num_bins - 1));
				float CDF_value = CDFs[channel][binIndex];
				pixelValue[channel] = CDF_value * (maxValues[channel] - minValues[channel]) + minValues[channel];
			}
			output.setValue(x, y, pixelValue);
		}
	}
}

void ImageProcessor::isolateBlacks(Image const & input, Image & output)
{
	output.clear();
	output = input;

	float WHITE_POINT = 1.0f;

	int const channelCount = input.getChannelCount();
	int const height = input.getHeight();
	int const width = input.getWidth();
	float max_value = input.getMaxValue();

#pragma omp parallel for
	for(int y = 0; y < height; y++)
	{
		Pixel pixelValue(channelCount, 0.0f);
		for(int x = 0; x < width; x++)
		{
			input.getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				if(pixelValue[channel] > 0)
				{
					pixelValue[channel] = std::max(WHITE_POINT, max_value);
				}
			}
			output.setValue(x, y, pixelValue);
		}
	}
}

// void ImageProcessor::coherentSubtraction(Image const & input, Image & output, size_t subtractedFrom, size_t subtractedWith)
// {
//     output.clear();
//     output = input;

//     int const channelCount = input.getChannelCount();
//     int const height = input.getHeight();
//     int const width = input.getWidth();

//     auto channel_averages = input.getChannelAverages();

//     std::cout << "Coveriance matrix: \n";
//     for(int i = 0; i < channelCount; i++)
//     {
//         for(int j = 0; j < channelCount; j++)
//         {
//             std::cout << input.getCovarianceMatrix()[i][j] << " ";
//         }
//         std::cout << "\n";
//     }

//     std::cout << "Correlation matrix: \n";
//     for(int i = 0; i < channelCount; i++)
//     {
//         for(int j = 0; j < channelCount; j++)
//         {
//             std::cout << input.getCorrelationMatrix()[i][j] << " ";
//         }
//         std::cout << "\n";
//     }

//     Image normalizedImage = input;

//     #pragma omp parallel for
// 	for(int y = 0; y < height; y++)
// 	{
// 		Pixel pixelValue(channelCount, 0.0f);
// 		for(int x = 0; x < width; x++)
// 		{
// 			input.getValue(x, y, pixelValue);
// 			for(int channel = 0; channel < channelCount; channel++)
// 			{
//                 pixelValue[channel] = pixelValue[channel] - channel_averages[channel];
// 			}
// 			normalizedImage.setValue(x, y, pixelValue);
// 		}
// 	}

//     output.clear();
//     output = input;

//     #pragma omp parallel for
//     for(int y = 0; y < height; y++)
//     {
//         Pixel pixelValue(channelCount, 0.0f);
//         for(int x = 0; x < width; x++)
//         {
//             input.getValue(x, y, pixelValue);
//             float subtracted_value = pixelValue[subtractedFrom] - pixelValue[subtractedWith];
//             for(int channel = 0; channel < channelCount; channel++)
//             {
//                 pixelValue[channel] = subtracted_value;
//             }
//             output.setValue(x, y, pixelValue);
//         }
//     }

// }


void ImageProcessor::coherentSubtraction(Image const & input, Image & output, size_t subtractedFrom, size_t subtractedWith)
{
	output.clear();
	output = input;

	int const channelCount = input.getChannelCount();
	int const height = input.getHeight();
	int const width = input.getWidth();

	auto const channel_averages = input.getChannelAverages();
	auto const cov_matrix = input.getCovarianceMatrix();
	auto const a = input.calculateA(subtractedFrom, subtractedWith);

	std::cout << "Coveriance matrix of original: \n";
	for(int i = 0; i < channelCount; i++)
	{
		for(int j = 0; j < channelCount; j++)
		{
			std::cout << cov_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	Image normalizedImage = input;

#pragma omp parallel for
	for(int y = 0; y < height; y++)
	{
		Pixel pixelValue(channelCount, 0.0f);
		for(int x = 0; x < width; x++)
		{
			input.getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				pixelValue[channel] = pixelValue[channel] - channel_averages[channel];
			}
			normalizedImage.setValue(x, y, pixelValue);
		}
	}

	std::cout << "Coveriance matrix of normalized: \n";
	auto const norm_cov_matrix = normalizedImage.getCovarianceMatrix();
	for(int i = 0; i < channelCount; i++)
	{
		for(int j = 0; j < channelCount; j++)
		{
			std::cout << norm_cov_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	output.clear();
	output = input;

#pragma omp parallel for
	for(int jRow = 0; jRow < height; jRow++)
	{
		Pixel pixelValue(channelCount, 0.0f);
		for(int iCol = 0; iCol < width; iCol++)
		{
			normalizedImage.getValue(iCol, jRow, pixelValue);
			float subtracted_value = pixelValue[subtractedFrom] - (a * pixelValue[subtractedWith]);
			for(int channel = 0; channel < channelCount; channel++)
			{
				pixelValue[channel] = subtracted_value;
			}
			output.setValue(iCol, jRow, pixelValue);
		}
	}
}

void ImageProcessor::applyImageDifference(Image const & subtractFrom, Image const & subtractWith, Image & output)
{
	output.clear();
	output = subtractFrom;

	int const channelCount = subtractFrom.getChannelCount();
	int const height = subtractFrom.getHeight();
	int const width = subtractFrom.getWidth();

	bool error = false;
	if(subtractFrom.getChannelCount() != subtractWith.getChannelCount()) {
		std::cout << "Error: Images must have the same number of channels.\n";
		std::cout << "subtractFrom.getChannelCount(): " << subtractFrom.getChannelCount() << "\n";
		std::cout << "subtractWith.getChannelCount(): " << subtractWith.getChannelCount() << "\n";
		error = true;
	}
	if(subtractFrom.getHeight() != subtractWith.getHeight()) {
		std::cout << "Error: Images must have the same height.\n";
		std::cout << "subtractFrom.getHeight(): " << subtractFrom.getHeight() << "\n";
		std::cout << "subtractWith.getHeight(): " << subtractWith.getHeight() << "\n";
		error = true;
	}
	if(subtractFrom.getWidth() != subtractWith.getWidth()) {
		std::cout << "Error: Images must have the same width.\n";
		std::cout << "subtractFrom.getWidth(): " << subtractFrom.getWidth() << "\n";
		std::cout << "subtractWith.getWidth(): " << subtractWith.getWidth() << "\n";
		error = true;
	}
	if(error) {
		return;
	}

#pragma omp parallel for
	for(int jRow = 0; jRow < height; jRow++)
	{
		Pixel difference(channelCount, 0.0f);
		Pixel subtrahend(channelCount, 0.0f);
		Pixel minuend(channelCount, 0.0f);
		for(int iCol = 0; iCol < width; iCol++)
		{
			subtractFrom.getValue(iCol, jRow, subtrahend);
			subtractWith.getValue(iCol, jRow, minuend);
			for(int channel = 0; channel < channelCount; channel++)
			{
				difference[channel] = subtrahend[channel] - minuend[channel];
			}
			output.setValue(iCol, jRow, difference);
		}
	}
}

#include "ImageProcessor.h"

using namespace image;

void ImageProcessor::applyGamma(float gamma, Image & imageToAlter)
{
	float * pRawData = imageToAlter.getRawData();

#pragma omp parallel for
	for(long elementIndex = 0; elementIndex < imageToAlter.getNumElements(); elementIndex++)
	{
		pRawData[elementIndex] = std::pow(pRawData[elementIndex], gamma);
	}
}

void ImageProcessor::doBoundedLinearConvolution(Stencil const & stencil, Image const & input, Image & output)
{
	output.clear();
	output = input;

	// Iterate through each row

#pragma omp parallel for
	for(int imageRowIndex = 0; imageRowIndex < output.getHeight(); imageRowIndex++)
	{
		// Iterate through each pixel in the row
		for(int pixelIndex = 0; pixelIndex < output.getWidth(); pixelIndex++)
		{
			// Initialize pixel that will contain weighted sum of neighborhood
			std::vector<float> outputPixel(output.getChannelCount(), 0.0);
			std::vector<float> sample(input.getChannelCount(), 0.0);

			// Iterate through each row of the neighborhood
			int bottomNeighbor = imageRowIndex - stencil.getHalfwidth();
			int topNeighbor = imageRowIndex + stencil.getHalfwidth();
			for(int neighborRow = bottomNeighbor; neighborRow <= topNeighbor; neighborRow++)
			{
				// Define stencil-space vertical index of current stencil row
				int stencilRow = neighborRow - imageRowIndex;

				// Define image-space vertical index of current stencil row
				int sampleRow = neighborRow;

				// Iterate through each column of the neighborhood in the current row
				int leftmostNeighbor = pixelIndex - stencil.getHalfwidth();
				int rightmostNeighbor = pixelIndex + stencil.getHalfwidth();
				for(int neighborPixel = leftmostNeighbor; neighborPixel <= rightmostNeighbor; neighborPixel++)
				{
					// Define stencil-space horizontal index of current stencil column
					int stencilCol = neighborPixel - pixelIndex;

					// Define image-space horizontal index of current stencil column
					int sampleCol = neighborPixel;

					// Retrieve stencil value at current stencil row and column
					float const & stencil_value = stencil(stencilCol, stencilRow);

					// If sample coordinates are outside of image bounds, set sample pixel to black
					// else, fill sample pixel with values from sample image

					if(sampleCol < 0 || sampleCol >= output.getWidth()
					|| sampleRow < 0 || sampleRow >= output.getHeight())
					{
						std::fill(sample.begin(), sample.end(), 0.0f);
					} else
					{
						input.getValue(sampleCol, sampleRow, sample);
					}

					// Iterate through each channel of the pixel
					for(size_t channelIndex = 0; channelIndex < sample.size(); channelIndex++)
					{
						// Apply weight to current channel of current pixel
						float weightedValue = sample[channelIndex] * stencil_value;

						// Increment value of current channel of current pixel by weighted value of given neighborhood pixel channel
						outputPixel[channelIndex] = outputPixel[channelIndex] + weightedValue;
					}
				}
			} // end iteration through each row of the neighborhood

			// Assign given pixel containing weighted sum of neighborhood to output image's equivalent pixel
			output.setValue(pixelIndex, imageRowIndex, outputPixel);

		} // end iteration through each pixel in the row
	}
}

void ImageProcessor::doCircularLinearConvolution(Stencil const & stencil, Image const & input, Image & output)
{
	output.clear();
	output = input;

#pragma omp parallel for
	for(int imageRowIndex = 0; imageRowIndex < output.getHeight(); imageRowIndex++) {

		int bottomNeighbor = imageRowIndex - stencil.getHalfwidth();
		int topNeighbor = imageRowIndex + stencil.getHalfwidth();

		for(int pixelIndex = 0; pixelIndex < output.getWidth(); pixelIndex++) {

			int leftmostNeighbor = pixelIndex - stencil.getHalfwidth();
			int rightmostNeighbor = pixelIndex + stencil.getHalfwidth();

			std::vector<float> outputPixel(output.getChannelCount(), 0.0);
			std::vector<float> sample(input.getChannelCount(), 0.0);

			for(int neighborRow = bottomNeighbor; neighborRow <= topNeighbor; neighborRow++) {

				int stencilRow = neighborRow - imageRowIndex;
				int sampleRow = neighborRow;

				// Handle neighborhood values outside of vertical bounds

				if(sampleRow < 0)                   sampleRow += output.getHeight();
                if(sampleRow >= output.getHeight()) sampleRow -= output.getHeight();

				for(int neighborPixel = leftmostNeighbor; neighborPixel <= rightmostNeighbor; neighborPixel++)
				{
					int stencilCol = neighborPixel - pixelIndex;
					int sampleCol = neighborPixel;

					if(sampleCol < 0)                  sampleCol += output.getWidth();
					if(sampleCol >= output.getWidth()) sampleCol -= output.getWidth();

					float const & stencil_value = stencil(stencilCol, stencilRow);

					input.getValue(sampleCol, sampleRow, sample);

					for(size_t channelIndex = 0; channelIndex < sample.size(); channelIndex++)
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

#include "Image.h"

#include <OpenImageIO/imageio.h>

using namespace OIIO;
using namespace image;

Image::Image()
: width(0)
, height(0)
, channelCount(0)
, numElements(0)
, pRawData(nullptr)
, normalizationData()
{
}

void Image::clear()
{
	if(pRawData)
	{
		delete[] pRawData;
		pRawData = nullptr;
	}
	width = 0;
	height = 0;
	channelCount = 0;
	numElements = 0;
}

bool Image::load(String const & filename)
{
	auto input = ImageInput::open(filename);
	if(! input) return false;

	ImageSpec const & spec = input->spec();
	this->width = spec.width;
	this->height = spec.height;
	this->channelCount = spec.nchannels;
	this->numElements = this->width * this->height * this->channelCount;

	this->pRawData = new float[this->numElements];

	input->read_image(TypeDesc::FLOAT, this->pRawData);

	input->close();

	return true;
}

bool file_exists(std::string const & name)
{
	std::ifstream file_stream(name.c_str());
	bool existence = file_stream.good();
	return existence;
}

bool Image::writeJPG(String const & baseName, String & outputName) const
{
	if(pRawData == nullptr) return false;

	String const EXTENSION = ".jpg";

	outputName = baseName + EXTENSION;
	while(file_exists(outputName))
		outputName.insert(outputName.size() - EXTENSION.size(), ".edited");


	auto output = ImageOutput::create(outputName);
	if(! output) return false;

	ImageSpec spec(width, height, channelCount, TypeDesc::FLOAT);
	output->open(outputName, spec);
	output->write_image(TypeDesc::FLOAT, pRawData);
	output->close();

	return true;
}

bool Image::writeEXR(String const & baseName, String & outputName) const
{
	if(pRawData == nullptr) return false;

	String const EXTENSION = ".exr";

	outputName = baseName + EXTENSION;
	while(file_exists(outputName))
		outputName.insert(outputName.size() - EXTENSION.size(), ".edited");

	auto output = ImageOutput::create(outputName);
	if(! output) return false;

	ImageSpec spec(width, height, channelCount, TypeDesc::FLOAT);
	output->open(outputName, spec);
	output->write_image(TypeDesc::FLOAT, pRawData);
	output->close();

	return true;
}

bool Image::writeText(String const & baseName, String & outputName) const
{

	int const PRECISION = 9;
	int const VALUE_WIDTH = 12;

	if(pRawData == nullptr) return false;

	String const EXTENSION = ".txt";
	outputName = baseName + EXTENSION;

	// Check if file exists and modify the name if it does
	while(file_exists(outputName))
	{
		outputName.insert(outputName.size() - EXTENSION.size(), "_edited");
	}

	// Open file stream for writing
	std::ofstream outFile(outputName);
	if(! outFile.is_open()) return false;


	// Write header information
	outFile << "P3\n"
		<< width << "\t" << height << "\n"
		<< getMinValue() << "\t" << getMaxValue() << "\n";

	// Write pixel data
	for(int i = 0; i < width * height * channelCount; i += channelCount)
	{
		for(int j = 0; j < channelCount; ++j)
		{
			outFile << std::right << std::fixed << std::setprecision(PRECISION) << std::setw(VALUE_WIDTH) << pRawData[i + j] << " ";
		}
		outFile << "\n";
	}

	// Close the file
	outFile.close();

	return true;
}

float Image::getMaxValue() const
{
	float maxValue = std::numeric_limits<float>::lowest();
	for(long i = 0; i < numElements; i++)
	{
		maxValue = std::max(maxValue, pRawData[i]);
	}
	return maxValue;
}

float Image::getMinValue() const
{
	float minValue = std::numeric_limits<float>::max();
	for(long i = 0; i < numElements; i++)
	{
		minValue = std::min(minValue, pRawData[i]);
	}
	return minValue;
}

void Image::clear(int newWidth, int newHeight, int newChannelCount)
{
	clear();
	width = newWidth;
	height = newHeight;
	channelCount = newChannelCount;
	numElements = (long)width * (long)height * (long)channelCount;
	normalizationData.clear();

	pRawData = new float[numElements];

#pragma omp parallel for
	for(long i = 0; i < numElements; i++)
	{
		pRawData[i] = 0.0;
	}
}

Image::Image(Image const & imageToCopy)
: width(imageToCopy.width)
, height(imageToCopy.height)
, channelCount(imageToCopy.channelCount)
, numElements(imageToCopy.numElements)
, normalizationData(imageToCopy.normalizationData)
{
	pRawData = new float[numElements];

#pragma omp parallel for
	for(long i = 0; i < numElements; i++)
	{
		pRawData[i] = imageToCopy.pRawData[i];
	}
}

Image::~Image()
{
	clear();
}

Image & Image::operator= (Image const & rhsImage)
{
	if(this == &rhsImage)
	{
		return *this;
	}

	if(width != rhsImage.width
	|| height != rhsImage.height
	|| channelCount != rhsImage.channelCount)
	{
		clear(rhsImage.width, rhsImage.height, rhsImage.channelCount);
	}

#pragma omp parallel for
	for(long i = 0; i < numElements; i++)
	{
		pRawData[i] = rhsImage.pRawData[i];
	}

	normalizationData = rhsImage.normalizationData;

	return *this;
}

void Image::getValue(int iCol, int jRow, std::vector<float> & pixel) const
{
	pixel.clear();

	if(pRawData == nullptr
	|| iCol < 0 || iCol >= width
	|| jRow < 0 || jRow >= height)
	{
		std::cerr << "Could not get value at (" << iCol << ", " << jRow << ")\n";
		return;
	}

	pixel.resize(channelCount);
	for(int channel = 0; channel < channelCount; channel++)
	{
		pixel[channel] = pRawData[index(iCol, jRow, channel)];
	}
	return;
}

// assigns requested set of values from given pixel indices into inputted pixel
// vector
void Image::setValue(int iCol, int jRow, Pixel const & pixel)
{
	size_t const pixelChannelCount = pixel.size();
	size_t const channel_count = getChannelCount();

	if(pRawData == nullptr
	|| iCol < 0 || iCol >= width
	|| jRow < 0 || jRow >= height
	|| channel_count > (int)(pixelChannelCount))
	{
		std::cerr << "Could not set value at (" << iCol << ", " << jRow << ")\n";
		return;
	}

#pragma omp parallel for
	for(int channel = 0; channel < channelCount; channel++)
	{
		pRawData[index(iCol, jRow, channel)] = pixel[channel];
	}
	return;
}

// interleaved index
long Image::index(int iCol, int jRow, int channel) const
{
	if(pRawData == nullptr
	|| iCol < 0 || iCol >= width
	|| jRow < 0 || jRow >= height)
	{
		std::cerr << "Could not get element index for channel at (";
		std::cerr << iCol << ", " << jRow << ", " << channel << ")\n";
	}

	long channelMultiplier = long(channelCount);
	long rowMultiplier = long(jRow) * long(width);
	long pixelMultiplier = long(iCol) + rowMultiplier;

	long pixelIndex = pixelMultiplier * channelMultiplier;
	long channelIndex = pixelIndex + (long)channel;

	return channelIndex;
}

Image::RawImageValues Image::getVerticallyFlippedData() const
{
	int const rowSize = width * channelCount;
	int const topIndex = height - 1;

	RawImageValues flippedData = new float[numElements];

	for(int rowIndex = 0; rowIndex < height; rowIndex++)
	{
		int flippedRowIndex = topIndex - rowIndex;
		for(int element = 0; element < rowSize; element++)
		{
			int originalPosition = rowIndex * rowSize + element;
			int flippedPosition = flippedRowIndex * rowSize + element;

			flippedData[flippedPosition] = pRawData[originalPosition];
		}
	}

	return flippedData;
}

Image::Pixel Image::getChannelAverages() const
{
	Pixel channelAverages(getChannelCount(), 0.0f);
	Pixel channelValueSums(getChannelCount(), 0.0f);

#pragma omp parallel
	{
		Pixel localSums(getChannelCount(), 0.0f);
		Pixel pixelValue(getChannelCount(), 0.0f);

		// Parallelize the outer loop
#pragma omp for
		for(int y = 0; y < getHeight(); y++)
		{
			for(int x = 0; x < getWidth(); x++)
			{
				getValue(x, y, pixelValue);
				for(int channel = 0; channel < getChannelCount(); channel++)
				{
					localSums[channel] += pixelValue[channel];
				}
			}
		}

		// Combine local sums into the global sum
#pragma omp critical
		for(int channel = 0; channel < getChannelCount(); channel++) {
			channelValueSums[channel] += localSums[channel];
		}
	}

	// Compute averages outside of the parallel region
	for(int channel = 0; channel < getChannelCount(); channel++) {
		float average = channelValueSums[channel] / getPixelCount();
		channelAverages[channel] = average;
	}

	return channelAverages;
}

Image::Pixel Image::getChannelRMSs() const
{

	Pixel const channelAverages = getChannelAverages();
	int const channelCount = getChannelCount();

	Pixel pixelValue(channelCount, 0.0f);

	// Calculate the sum of squared differences for RMS
	Pixel sumsOfSquares(channelCount, 0.0f);
	for(int y = 0; y < getHeight(); y++)
	{
		for(int x = 0; x < getWidth(); x++)
		{
			getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				float pixelChannelDeviation = pixelValue[channel] - channelAverages[channel];
				sumsOfSquares[channel] += pixelChannelDeviation * pixelChannelDeviation;
			}
		}
	}

	// Calculate the RMS for each channel
	Pixel channelRMSs(channelCount, 0.0f);
	for(int channel = 0; channel < channelCount; channel++)
	{
		channelRMSs[channel] = std::sqrt(sumsOfSquares[channel] / getPixelCount());
	}

	return channelRMSs;
}

std::vector<Image::Pixel> Image::getCovarianceMatrix(void) const
{
	using std::vector;

	Pixel const channelAverages = getChannelAverages();
	int const channelCount = getChannelCount();

	Pixel pixelValue(channelCount, 0.0f);

	vector<Pixel> covarianceMatrix(channelCount, Pixel(channelCount, 0.0f));

	for(int y = 0; y < getHeight(); y++)
	{
		for(int x = 0; x < getWidth(); x++)
		{
			getValue(x, y, pixelValue);
			for(int row = 0; row < channelCount; row++)
			{
				for(int col = 0; col < channelCount; col++)
				{
					float rowDeviation = pixelValue[row] - channelAverages[row];
					float colDeviation = pixelValue[col] - channelAverages[col];
					covarianceMatrix[row][col] += rowDeviation * colDeviation;
				}
			}
		}
	}

	for(int row = 0; row < channelCount; row++)
	{
		for(int col = 0; col < channelCount; col++)
		{
			covarianceMatrix[row][col] /= getPixelCount();
		}
	}

	return covarianceMatrix;
}

std::vector<Image::Pixel> Image::getCorrelationMatrix(void) const
{

	using std::vector;

	vector<Pixel> const covarianceMatrix = getCovarianceMatrix();
	Pixel const channelRMSs = getChannelRMSs();
	int const channelCount = getChannelCount();

	vector<Pixel> correlationMatrix(channelCount, Pixel(channelCount, 0.0f));

	for(int row = 0; row < channelCount; row++)
	{
		for(int col = 0; col < channelCount; col++)
		{
			correlationMatrix[row][col] = covarianceMatrix[row][col] / (channelRMSs[row] * channelRMSs[col]);
		}
	}

	return correlationMatrix;
}

float Image::calculateA(int subtractedFrom, int subtractedWith) const
{

	const auto cov_matrix = getCovarianceMatrix();

	if(cov_matrix.size() < std::max(subtractedFrom, subtractedWith)
	|| cov_matrix[0].size() <= 1)
	{
		return 0.0f; // not enough data
	}
	if(cov_matrix[subtractedWith][subtractedWith] == 0.0f) return 0.0f; // avoid division by zero


	auto A = cov_matrix[subtractedWith][subtractedFrom] / cov_matrix[subtractedWith][subtractedWith];

	return A;
}

void Image::calculateHistograms(std::vector<std::vector<int>> & histograms, Pixel & minValues, Pixel & maxValues, int numBins) const
{
	using std::max;
	using std::min;
	using std::numeric_limits;

	int const channelCount = getChannelCount();
	int const height = getHeight();
	int const width = getWidth();

	Pixel pixelValue(channelCount, 0.0f);

	histograms.assign(channelCount, std::vector<int>(numBins, 0));
	minValues.assign(channelCount, numeric_limits<float>::max());
	maxValues.assign(channelCount, numeric_limits<float>::lowest());

	// Find min and max values for each channel and fill histograms
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				minValues[channel] = min(minValues[channel], pixelValue[channel]);
				maxValues[channel] = max(maxValues[channel], pixelValue[channel]);
			}
		}
	}

	// Fill histograms
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			getValue(x, y, pixelValue);
			for(int channel = 0; channel < channelCount; channel++)
			{
				if(maxValues[channel] == minValues[channel]) continue; // Avoid division by zero

				int binIndex = static_cast<int>((pixelValue[channel] - minValues[channel]) / (maxValues[channel] - minValues[channel]) * (numBins - 1));
				binIndex = max(0, min(binIndex, numBins - 1)); // Ensure bin index is within valid range
				histograms[channel][binIndex]++;
			}
		}
	}
}

void Image::normalizeHistograms(std::vector<std::vector<int>> const & histograms, std::vector<std::vector<float>> & normalizedHistograms, int totalPixels) const
{
	int channelCount = histograms.size();
	int numBins = histograms[0].size();
	normalizedHistograms.assign(channelCount, std::vector<float>(numBins, 0.0f));

	for(int channel = 0; channel < channelCount; channel++)
	{
		for(int bin = 0; bin < numBins; bin++)
		{
			normalizedHistograms[channel][bin] = static_cast<float>(histograms[channel][bin]) / totalPixels;
		}
	}
}

void Image::computeCDFs(std::vector<std::vector<float>> const & normalizedHistograms, std::vector<std::vector<float>> & CDFs) const
{
	int channelCount = normalizedHistograms.size();
	int numBins = normalizedHistograms[0].size();
	CDFs.assign(channelCount, std::vector<float>(numBins, 0.0f));

	for(int channel = 0; channel < channelCount; channel++)
	{
		CDFs[channel][0] = normalizedHistograms[channel][0];
		for(int bin = 1; bin < numBins; bin++)
		{
			CDFs[channel][bin] = CDFs[channel][bin - 1] + normalizedHistograms[channel][bin];
		}
	}
}

// void Image::printPixelValues(Pixel const & pixel) const
// {

// 	std::cout << "(";
// 	for(int channelIndex = 0; channelIndex < (int)(pixel.size()); channelIndex++)
// 	{
// 		std::cout << std::fixed << std::setprecision(4)
// 			  << pixel[channelIndex];

// 		if(channelIndex < channelCount - 1)
// 		{
// 			std::cout << ",";
// 		}
// 	}
// 	std::cout << ") ";

// 	return;
// }

// bool Image::isValid() const
// {

// 	if(! pRawData
// 	|| width <= 0
// 	|| height <= 0
// 	|| channelCount <= 0
// 	|| numElements <= 0)
// 	{
// 		return false;
// 	}

// 	return true;
// }

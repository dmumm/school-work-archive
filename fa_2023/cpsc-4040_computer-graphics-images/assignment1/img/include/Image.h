#ifndef IMAGE_H
#define IMAGE_H

#include <fstream> // Required to check if file exists
#include <string>
#include <vector>
#include <iomanip> // for std::setw

namespace image {

class Image {

      public:

	using Histogram = std::vector<int>;
	using HistogramArray = std::vector<Histogram>;
	using NormalizedHistogram = std::vector<float>;
	using NormalizedHistogramArray = std::vector<NormalizedHistogram>;
	using FloatArray = std::vector<float>;
	using Pixel = std::vector<float>;
	using RawImageValues = float *;
    using String = std::string;
    using ChannelNormalizationData = std::vector<Pixel>;


	// ImgProc();
	Image();

	// ~ImgProc();
	~Image();

	void clear();
	void clear(int width, int height, int channelCount);

	bool load(String const & filename);

	bool writeJPG(String const & baseName, String & outputName) const;
	bool writeEXR(String const & baseName, String & outputName) const;
    bool writeText(String const & baseName, String & outputName) const;

    float getMaxValue() const;
    float getMinValue() const;

    int getWidth() const
    {
	    return width;
	}

	int getHeight() const
	{
		return height;
	}

	int getChannelCount() const
	{
		return channelCount;
	}

	long getNumElements() const
	{
		return numElements;
	}

    ChannelNormalizationData getNormalizationData() const
    {
        return normalizationData;
    }

    void setNormalizationData(ChannelNormalizationData const & normalizationData)
    {
        this->normalizationData = normalizationData;
    }

	int getPixelCount() const
	{
		return getWidth() * getHeight();
	}

	RawImageValues getRawData() const
	{
		return pRawData;
	} // img_data(), retrive pointer to the raw data

	void getValue(int iCol, int jRow, Pixel & pixel) const;
	void setValue(int iCol, int jRow, Pixel const & pixel);
	//  void interpolated_value( float iCol, float jRow, Pixel& pixel) const;

	Image(Image const & imageTwo);
	Image & operator= (Image const & imageTwo);

	//  friend void swap(Image& imageOne, Image& imageTwo);

	//  void operator*=(float value);
	//  void operator/=(float value);
	//  void operator+=(float value);
	//  void operator-=(float value);
	//  void operator-=(const Image& imageTwo);
	//  void operator+=(const Image& imageTwo);

	//  void compliment();
	//  void negative();
	//  void pow(float gamma);
	//  void quantize(int levels);
	//  void grayscale();
	//  void rms_contrast();
	//  void demean();
	//  void log();
	//  void exp();

	//  void flip();
	//  void flop();

	//  void tanh( const Pixel rms);
	//  void quench();
	//  void logquench();

	//  void rgb_to_hsv();
	//  void hsv_to_rgb();
	//  void rgb_to_cmyk();
	//  void cmyk_to_rgb(const float K);

	//  void edge_taper(int nb);

	long index(int iCol, int jRow, int channel) const; // i, j, c
	// long index(int iCol, int jRow) const; // i, j

	// void printPixelValues(Pixel const &) const;

	// bool isValid() const;

	RawImageValues getVerticallyFlippedData() const;

	Pixel getChannelAverages() const;
	Pixel getChannelRMSs() const;
	std::vector<Pixel> getCovarianceMatrix() const;
	std::vector<Pixel> getCorrelationMatrix() const;

	float calculateA(int subtractedFrom, int subtractedWith) const;


	void calculateHistograms(HistogramArray &, FloatArray &, FloatArray &, int) const;
	void normalizeHistograms(HistogramArray const &, NormalizedHistogramArray &, int) const;
	void computeCDFs(NormalizedHistogramArray const &, NormalizedHistogramArray &) const;



      private:

	int width, height, channelCount; // Nx, Ny, Nc
	long numElements; // Nsize (width * height * channelCount)
	RawImageValues pRawData; // img_data
    ChannelNormalizationData normalizationData;
};

//  void swap(Image& imageOne, Image& imageTwo);

} // namespace image
#endif // IMAGE_H

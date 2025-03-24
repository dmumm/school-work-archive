#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "Image.h"
#include "FractalSet.h"
#include "Stencil.h"

#include <cmath> // for std::pow
#include <algorithm>  // for std::fill
#include <limits> // for FLT_MAX

namespace image {

class ImageProcessor {

  public:

    using Histogram = std::vector<int>;
    using NormalizedHistogram = std::vector<float>;
    using HistogramArray = std::vector<Histogram>;
    using NormalizedHistogramArray = std::vector<NormalizedHistogram>;
    using FloatArray = std::vector<float>;
    using Pixel = std::vector<float>;
    using RawImageValues = float *;
    using String = std::string;
    using ChannelNormalizationData = std::vector<Pixel>;

    static void applyGamma(float gamma, Image & inputImage);
    static void applyNormalizedGamma(float gamma, Image & inputImage);

    static void applyBrightness(float multiplier, Image & inputImage);
    static void applyBias(const Pixel bias, Image & inputImage);

    // Applies linear convolution on the given image
    static void doCircularLinearConvolution(Stencil const & stencil, const Image & imageToReadFrom, Image & imageToWriteTo);
    static void doBoundedLinearConvolution(Stencil const & stencil, const Image & imageToReadFrom, Image & imageToWriteTo);

    // Applies contrast transformation on the given image via average and RMS
    static ChannelNormalizationData applyContrastNormalization(const Image & imageToReadFrom, Image & imageToWriteTo);
    static void reverseContrastNormalization(const ChannelNormalizationData & normalizationData, const Image & imageToReadFrom, Image & imageToWriteTo);
    static void applyHistogramEqualization(int num_bins, const Image & imageToReadFrom, Image & imageToWriteTo);

    static void isolateBlacks(const Image & imageToReadFrom, Image & imageToWriteTo);

    static void coherentSubtraction(Image const & input, Image & output, size_t subtractedFrom, size_t subtractedwith);

    static void applyImageDifference(Image const & subtractFrom, Image const & subtractWith, Image & output);


  private:
}; // class ImageProcessor

} // namespace image

#endif // IMAGE_PROCESSOR_H

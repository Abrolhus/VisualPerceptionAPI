#ifndef IMAGESEGMENTER_H
#define IMAGESEGMENTER_H
#include "Image_Region.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>


#define IM_MEDIAN 0
#define IM_MEAN 1
/** Responsible for transforming images into small matrices of Regions.
 *
 */
class SegmentedImage
{
public:
    SegmentedImage(cv::Mat image);
    std::vector<std::vector<ImageRegion>>* regions;
};
#endif

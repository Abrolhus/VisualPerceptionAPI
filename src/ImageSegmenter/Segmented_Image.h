#ifndef SEGMENTED_IMAGE_H
#define SEGMENTED_IMAGE_H
#include "Image_Region.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <field_color_detection/field_color_detector.h>
/** Responsible for transforming images into small matrices of Regions.
 *
 */
class SegmentedImage
{
public:
    SegmentedImage(cv::Mat& image);
    std::vector<std::vector<ImageRegion>>* regions;
    void displaySegmentedImage() const;
    void displaySegmentedImageRegions() const;
private:
    int getWidth() const;
    int getHeight() const;
    cv::Vec3b bgr_median(std::vector<cv::Vec3b>& colors);
};
#endif

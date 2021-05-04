#ifndef IMAGESEGMENTER_H
#define IMAGESEGMENTER_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "ImageRegion.h"

#define UNKNOWN 0
#define FIELD 1
#define BACKGROUND 2

#define IM_MEDIAN 0
#define IM_MEAN 1
/** Responsible for transforming images into small matrices of Regions.
 *
 */
class ImageSegmenter
{
public:
    ImageSegmenter();
    /** Segments the image into smaller regions with the same dimensions. Each region is represented
     * by the accent color of its pixels. The resulting image is a pixelated version of the input.
     * Work in Progress
     *
     * @param[in] src[ input image
     * @param[out] dst Destination image (Debug)
     * @param[out] model matrix of regions
     * @param xjump steps in x direction
     * @param yjump steps in y direction
     */
    void segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<ImageRegion>> model, std::vector<uint8_t>& LUT, int xjump= 5,
                      int yjump= 5, int method= IM_MEDIAN);
    void segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<ImageRegion>> model, int xjump= 5,
                      int yjump= 5, int method= IM_MEDIAN);
    /** Labels one single Image segment/region
     *
     * @param segment region of the image.
     * @param LUT Look-up Table. Each key (vector position) represents a RGB color and each value its label. e.i position 156700 represents (255, 0, 100) and its value is 1. So if the region has this color value, it will be labeled as 1 (FIELD)
     */
    void label_image_segment(ImageRegion& segment, std::vector<uint8_t>& LUT);
};
#endif

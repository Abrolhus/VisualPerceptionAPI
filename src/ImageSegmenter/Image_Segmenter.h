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
class Image_Segmenter
{
public:
    Image_Segmenter();
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
    void segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<Image_Region>>& model, std::vector<uint8_t>& LUT, int xjump= 5,
                      int yjump= 5, int method= IM_MEDIAN);
    void segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<Image_Region>>& model, int xjump= 5,
                      int yjump= 5, int method= IM_MEDIAN);
    /** Labels one single Image segment/region
     *
     * @param segment region of the image.
     * @param LUT Look-up Table. Each key (vector position) represents a RGB color and each value its label. e.i position 156700 represents (255, 0, 100) and its value is 1. So if the region has this color value, it will be labeled as 1 (FIELD)
     */
    void label_image_segment(Image_Region& segment, std::vector<uint8_t>& LUT);
    cv::Vec3b bgr_to_hsv(cv::Vec3b);
};
#endif

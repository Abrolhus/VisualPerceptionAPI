//
// Created by abrolhus on 26/04/2021.
//

#ifndef VISUALPERCEPTION_IMAGE_REGION_H
#define VISUALPERCEPTION_IMAGE_REGION_H

#include <cstdint>
#include <opencv2/core/core.hpp>

#define UNKNOWN 0
#define FIELD 1
#define BACKGROUND 2

enum class RegionLabel {
    Field, 
    Background, 
    Unknown, 
}

/** Represents a retangular region of a image.
 *
 *
 */
class Image_Region
{
public:
    Image_Region(int x, int y, int w, int h, cv::Vec3b color, uint8_t label);
    Image_Region(int x, int y, int w, int h, const cv::Vec3b& color_bgr, const cv::Vec3b& color_hsv, uint8_t label);
    Image_Region(); // Default Constructor (for containers)
    uint8_t label; //< FIELD, BACKGROUND, ... //< FIELD, BACKGROUND, UNKNOWN ...
    int x; //< x position of the upper-right corner
    int y; //< y position of the upper-right corner
    int w; //< width of the rectangle
    int h; //< height of the rectangle
    // cv::Vec3b color_hsv;
    cv::Vec3b color; //< representing color, generally the median of the colors.
    // Image_Region& operator=(const Image_Region& other) noexcept;
};

#endif // VISUALPERCEPTION_IMAGE_REGION_H

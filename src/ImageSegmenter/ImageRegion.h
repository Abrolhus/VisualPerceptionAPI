//
// Created by abrolhus on 26/04/2021.
//

#ifndef VISUALPERCEPTION_IMAGEREGION_H
#define VISUALPERCEPTION_IMAGEREGION_H

#include <cstdint>
#include <opencv2/core/core.hpp>

/** Represents a retangular region of a image.
 *
 *
 */
class ImageRegion
{
public:
    ImageRegion(int x, int y, int w, int h, cv::Vec3b color, uint8_t label);
    ImageRegion(); // Default Constructor (for containers)
    uint8_t label; //< FIELD, BACKGROUND, ... //< FIELD, BACKGROUND, UNKNOWN ...
    int x; //< x position of the upper-right corner
    int y; //< y position of the upper-right corner
    int w; //< width of the rectangle
    int h; //< height of the rectangle
    cv::Vec3b color; //< representing color, generally the median of the colors.
    ImageRegion& operator=(const ImageRegion& other) noexcept;
};

#endif // VISUALPERCEPTION_IMAGEREGION_H

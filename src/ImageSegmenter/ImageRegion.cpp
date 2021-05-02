//
// Created by abrolhus on 26/04/2021.
//

#include "ImageRegion.h"

ImageRegion::ImageRegion(int x, int y, int w, int h, cv::Vec3b color, uint8_t label){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = color;
    this->label = label;
}
ImageRegion::ImageRegion()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->color = cv::Vec3b{0,0,0};
    this->label = 0;
}
ImageRegion& ImageRegion::operator=(const ImageRegion& other) noexcept {
    if (this == &other) { return *this; }
    this->color = other.color;
    this->x = other.x;
    this->y = other.y;
    // this->y= 7;
    this->w = other.w;
    this->h = other.h;
    this->label = other.label;
    // ...
    return *this;
}
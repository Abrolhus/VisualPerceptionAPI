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

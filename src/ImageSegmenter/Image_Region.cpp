//
// Created by abrolhus on 26/04/2021.
//

#include "Image_Region.h"

Image_Region::Image_Region(int x, int y, int w, int h, cv::Vec3b color_bgr, RegionLabel label){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = color_bgr;
    this->label = label;
}

Image_Region::Image_Region()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->color = cv::Vec3b{0,0,0};
    this->label = RegionLabel::Unknown;
}
#ifndef FIELD_COLOR_DETECTOR_H
#define FIELD_COLOR_DETECTOR_H
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
class Field_color_detector{
public:
    static float getChromaticity(uchar channelColor, Vec3b color);
    static void paintField(Mat imgInput);
    static bool isField(Vec3b pixel);
    Field_color_detector();
    ~Field_color_detector();
    static void paintNotField(Mat imgInput);
};
#endif


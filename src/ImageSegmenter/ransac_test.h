#ifndef RANSAC_TEST_H_
#define RANSAC_TEST_H_

#include "ransac2d.h"

bool testLine2d(SegmentedImage& segImg, Mat& image, cv::Vec4d& output_line);

#endif
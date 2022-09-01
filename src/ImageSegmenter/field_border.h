#ifndef FIELD_BORDER_H
#define FIELD_BORDER_H
#include "Image_Region.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <field_color_detection/field_color_detector.h>
/** Responsible for transforming images into small matrices of Regions.
 *
 */
    void scanline(SegmentedImage& segImg);
#endif

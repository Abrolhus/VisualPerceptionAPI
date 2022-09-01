#include <ImageSegmenter/Segmented_Image.h>
#include <ImageSegmenter/field_border.h>
#include <ImageSegmenter/ransac_test.h>
#include "dummy.h"
#include <file_proc/file_proc.h>
#include <img_proc/img_proc.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
    for(int i = 1; i < argc; i++){
        Mat img = imread(argv[i]);
        SegmentedImage segmentedImage(img);
        scanline(segmentedImage);
        testLine2d(segmentedImage, img);
        imshow("img", img);
        segmentedImage.displaySegmentedImage();
        segmentedImage.displaySegmentedImageRegions();
        waitKey();
    }
    return 0;
}

#include <ImageSegmenter/Segmented_Image.h>
#include "dummy.h"
#include <file_proc/file_proc.h>
#include <img_proc/img_proc.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
    Mat img = imread(argv[1]);
    SegmentedImage segmentedImage(img);
    imshow("img", img);
    segmentedImage.displaySegmentedImage();
    waitKey();
    return 0;
}

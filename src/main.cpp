#include "opencv2/opencv.hpp"
#include <iostream>
// #include "img_proc.h"
#include "dummy.h"
#include "img_proc/img_proc.h"

using namespace cv;

int main(int argc, const char** argv)
{
    std::cout << "Hello World"
              << " " << img_proc::somar(9, 4) << std::endl;
    std::cout << "Hello arquivo local:"
              << " " << somar(9, 4) << std::endl;
    Mat img = imread(argv[1]);

    Mat clusteredImg, clusters;

    img_proc::clustering(img, clusteredImg, clusters);
    imshow("img", img);
    imshow("clusteredImg", clusteredImg);
    Mat clusterse;
    cv::resize(clusters, clusterse, cv::Size(), 5, 5);
    imshow("clusters", clusterse);
    waitKey();
    return 0;
}

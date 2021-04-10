#include "opencv2/opencv.hpp"
#include <iostream>
// #include "img_proc.h"
#include "img_proc/img_proc.h"
#include "dummy.h"
using namespace cv;
int main(int argc, const char** argv){
    std::cout << "Hello World" << " " << img_proc::somar(9, 4)<< std::endl;
    std::cout << "Hello arquivo local:" << " " << somar(9, 4)<< std::endl;
    Mat img = imread(argv[1]);
    imshow("img", img);
    waitKey();
    return 0;
}



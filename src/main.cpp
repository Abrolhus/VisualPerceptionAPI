#include "opencv2/opencv.hpp"
#include <iostream>
#include "dummy.h"
#include "img_proc/img_proc.h"
#include "file_proc/file_proc.h"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
    std::cout << "Hello World" << " " << img_proc::somar(9, 4) << std::endl;
    std::cout << "Hello arquivo local:"
              << " " << somar(9, 4) << std::endl;
    Mat img = imread(argv[1]);

    Mat clusteredImg, clusters;
    Mat roi;
    vector<unsigned char> clusteredColors(256*256*256);
    file_proc::getColorClusters("../testeClustering.txt",  clusteredColors);
    cout << "vai" <<endl;
    for(int i = 0; i < clusteredColors.size(); i++){
        if(clusteredColors[i] == 1){
            cout << i << ", ";
        }
    }


    img_proc::clustering(img, clusteredImg, clusters, 10, 10);
    img_proc::getRoi(img, roi, 100, 100, 200, 200);
    imshow("img", img);
    imshow("ROI: ", roi);
    imshow("clusteredImg", clusteredImg);
    Mat clusterse;
    cv::resize(clusters, clusterse, cv::Size(), 5, 5);
    imshow("clusters", clusterse);
    waitKey();
    return 0;
}

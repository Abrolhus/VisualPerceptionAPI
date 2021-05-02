#include "opencv2/opencv.hpp"
#include <iostream>
#include "dummy.h"
#include "img_proc/img_proc.h"
#include "file_proc/file_proc.h"
#include "ImageSegmenter/ImageSegmenter.h"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
    Mat img = imread(argv[1]);
    Mat clusteredImg, clusters;
    //vector<uint8_t> LUT(256*256*256, 0);
    // file_proc::getColorClusters("clust.txt",  LUT);
    cout << "vai" <<endl;
    int count=0;
    //for(int i = 0; i < LUT.size(); i++){
        //if(LUT[i] == FIELD){
            //cout << hex << i << ", "; // all values are in BGR! (https://wamingo.net/rgbbgr/ -> BGR visualizer)
        //}
    //}
    // cout << endl;

    ImageSegmenter ImSeg;
    // Mat_<ImageRegion> model;
    vector<vector<ImageRegion>> model(img.rows/5, vector<ImageRegion>(img.cols/5, ImageRegion()));
    // model = cv::Mat_<ImageRegion>(img.rows/5, img.cols/5);
    // ImSeg.segmentImage(img, clusteredImg, model, LUT, 5, 5);
    ImSeg.segmentImage(img, clusteredImg, model, 5, 5);

    imshow("img", img);
    imshow("clusteredImg Median", clusteredImg);
    waitKey();
    return 0;
}

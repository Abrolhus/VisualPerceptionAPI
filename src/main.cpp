#include <ImageSegmenter/Image_Segmenter.h>
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
    Mat clusteredImg, clusters;
    //vector<uint8_t> LUT(256*256*256, 0);
    // file_proc::get_color_clusters("clust.txt",  LUT);
    cout << "vai" <<endl;
    int count=0;
    //for(int i = 0; i < LUT.size(); i++){
        //if(LUT[i] == FIELD){
            //cout << hex << i << ", "; // all values are in BGR! (https://wamingo.net/rgbbgr/ -> BGR visualizer)
        //}
    //}
    // cout << endl;

    Image_Segmenter ImSeg;
    // Mat_<Image_Region> model;
    vector<vector<Image_Region>> model(img.rows/5, vector<Image_Region>(img.cols/5, Image_Region()));
    // model = cv::Mat_<Image_Region>(img.rows/5, img.cols/5);
    // ImSeg.segment_image(img, clusteredImg, model, LUT, 5, 5);
    ImSeg.segment_image(img, clusteredImg, model, 5, 5);

    imshow("img", img);
    imshow("clusteredImg Median", clusteredImg);
    waitKey();
    return 0;
}

#include "img_proc.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

namespace img_proc {
    int somar(int a, int b){
        return a + b;
    }
    void clustering(cv::Mat &src, cv::Mat &dst, cv::Mat& model, int xjump, int yjump) {
        src.copyTo(dst); // TODO: delete this line
        model = cv::Mat(src.rows/yjump, src.cols/xjump,  CV_8UC3, cvScalar(0, 0, 0)); // note that wont work if xjump and yjump are not multipples of the respective image dimensions // TODO(Samuel): add assert
        imshow("teste", model);

        // ill call the segmented img a "model";
        for(int j = 0; j < model.rows; j++){
            for(int i = 0; i < model.cols; i++){
                cv::Vec3i sum{0, 0, 0};
                    for (int lj = 0; lj < yjump; lj++) {
                for (int li = 0; li < xjump; li++) {
                        sum += src.at<cv::Vec3b>(i*xjump + li, j*yjump + lj);
                    }
                }
                cv::Vec3b mean = sum/(xjump*yjump); // implicit casting from Vec3i to Vec3b
                model.at<cv::Vec3b>(i, j) = mean;
                    for (int lj = 0; lj < yjump; lj++) {
                for (int li = 0; li < xjump; li++) {
                        dst.at<cv::Vec3b>(i*xjump + li, j*yjump + lj) = mean;
                    }
                }
            }
        }







        // for (int i = 0; i < src.cols; i += xjump) {
//
            // for (int j = 0; j < src.rows; j += yjump) {
                // cv::Vec3i sum{0, 0, 0};
                // for (int li = 0; li < xjump; li++) {
                    // for (int lj = 0; lj < yjump; lj++) {
                        // std::cout << i + li << ", ";
                        // // sum += src.at<cv::Vec3b>(i+ li, j+ lj);
                        // sum += src.at<cv::Vec3b>(j+ lj, i+ li);
                    // }
                // }
                // cv::Vec3b mean = sum/(xjump*yjump); // implicit casting from Vec3i to Vec3b
                // clusters.at<cv::Vec3b>(j/yjump, i/xjump) = mean;  // TODO: assert that both int divisions are valid
                // for (int li = 0; li < xjump; li++) {
                    // for (int lj = 0; lj < yjump; lj++) {
                        // std::cout << i + li << ", ";
                        // dst.at<cv::Vec3b>(j + lj, i +li) = mean;
                    // }
                // }
//
            // }
        // }
        return;
    }

}

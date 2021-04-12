#include "img_proc.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

namespace img_proc {
    int somar(int a, int b){
        return a + b;
    }
    void clustering(cv::Mat &src, cv::Mat &dst, cv::Mat& clusters, int xjump, int yjump) {
        src.copyTo(dst); // TODO: delete this line
        clusters = cv::Mat(src.cols/xjump, src.rows/yjump, CV_8UC3); // note that wont work if xjump and yjump are not multipples of the respective image dimensions // TODO: add assert
        for (int i = 0; i < src.cols; i += xjump) {
            for (int j = 0; j < src.rows; j += yjump) {
                cv::Vec3i sum{0, 0, 0};
                for (int li = 0; li < xjump; li++) {
                    for (int lj = 0; lj < yjump; lj++) {
                        std::cout << i + li << ", ";
                        // sum += src.at<cv::Vec3b>(i+ li, j+ lj);
                        sum += src.at<cv::Vec3b>(j+ lj, i+ li);
                    }
                }
                cv::Vec3b mean = sum/(xjump*yjump); // implicit casting from Vec3i to Vec3b
                clusters.at<cv::Vec3b>(j/yjump, i/xjump) = mean;  // TODO: assert that both int divisions are valid
                for (int li = 0; li < xjump; li++) {
                    for (int lj = 0; lj < yjump; lj++) {
                        std::cout << i + li << ", ";
                        dst.at<cv::Vec3b>(j + lj, i +li) = mean;
                    }
                }

            }
        }
        return;
    }

}

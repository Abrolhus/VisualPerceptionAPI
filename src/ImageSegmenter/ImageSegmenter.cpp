#include "ImageSegmenter.h"
#include "opencv2/highgui/highgui.hpp"
#include "ImageRegion.h"
#include <exception>
#include <iostream>
void ImageSegmenter::segmentImage(cv::Mat& src, cv::Mat& dst, cv::Mat_<ImageRegion>& model, int xjump,
                                int yjump)
{
    src.copyTo(dst); // TODO(Abreu): delete this line
    model =
        cv::Mat(src.rows / yjump, src.cols / xjump, CV_8UC3,
                cvScalar(0, 0, 0)); // note that wont work if xjump and yjump are not multipples of
                                    // the respective image dimensions // TODO(Abreu): add assert
    // I'll call the segmented img a "model";
    for (int j = 0; j < model.rows; j++)
    {
        for (int i = 0; i < model.cols; i++)
        {
            cv::Vec3i sum{0, 0, 0};
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    sum += src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li);
                }
            }
            cv::Vec3b mean = sum / (xjump * yjump); // implicit casting from Vec3i to Vec3b
            model.at<cv::Vec3b>(j, i) = mean;
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = mean;
                }
            }
        }
    }
}

#include "img_proc.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <exception>
#include <algorithm>
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[2] < b[2]; }
} greaterRed;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[1] < b[1]; }
} greaterGreen;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[0] < b[0]; }
} greaterBlue;
namespace img_proc
{
int somar(int a, int b) { return a + b; }
void clustering(cv::Mat& src, cv::Mat& dst, cv::Mat& model, int xjump, int yjump, int method)
{
    // TODO(Abreu): add exceptions (e.i method != Median e Mean)
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
            std::vector<cv::Vec3b> allValues;
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    if (method == IM_MEAN){
                        sum += src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li);
                    }
                    if (method == IM_MEDIAN){
                        allValues.push_back(src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li));
                    }
                }
            }
            cv::Vec3b sample;
            if(method == IM_MEAN){
                sample = sum / (xjump * yjump); // implicit casting from Vec3i to Vec3b
            }
            if(method == IM_MEDIAN){
                std::sort(allValues.begin(), allValues.end(), greaterBlue);
                sample[0] = allValues.at(allValues.size()/2)[0];
                std::sort(allValues.begin(), allValues.end(), greaterGreen);
                sample[1] = allValues.at(allValues.size()/2)[1];
                std::sort(allValues.begin(), allValues.end(), greaterRed);
                sample[2] = allValues.at(allValues.size()/2)[2];
            }
            model.at<cv::Vec3b>(j, i) = sample;
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = sample;
                }
            }
        }
    }
}
void getRoi(cv::Mat& src, cv::Mat& roi, int x, int y, int width, int height)
{
    cv::Rect region(x, y, width, height);
    cv::Rect image(0, 0, src.cols, src.rows);
    if (image.contains(cv::Point(x, y)) && image.contains(cv::Point(x + width, y)) &&
        image.contains(cv::Point(x, y + height)) && image.contains(cv::Point(+width, y + height)))
    {
        cv::Mat aux = cv::Mat(src, region);
        aux.copyTo(roi);
    }
    else
    {
        throw std::invalid_argument("Region not within image boundaries");
    }
}
}; // namespace img_proc

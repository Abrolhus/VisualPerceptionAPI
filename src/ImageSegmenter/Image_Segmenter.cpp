#include "Image_Segmenter.h"
#include "opencv2/core/core.hpp"
#include <exception>
#include <iostream>
// #include "../img_proc/img_proc.h"
#include <img_proc/img_proc.h>
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[2] < b[2]; }
} greaterRed;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[1] < b[1]; }
} greaterGreen;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[0] < b[0]; }
} greaterBlue;

Image_Segmenter::Image_Segmenter() = default;
void Image_Segmenter::segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<Image_Region>>& model, std::vector<uint8_t>& LUT,
                                  int xjump, int yjump, int method)
{
    src.copyTo(dst); // TODO(Abreu): delete this line
    assert(src.rows % yjump == 0 && src.cols % xjump == 0);
    //model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump, new Image_Region());
    // model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump );
    // model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump, 10);

    // note that wont work if xjump and yjump are not multipples of
                                    // the respective image dimensions // TODO(Abreu): add assert
    // I'll call the segmented img a "model";
    for (int j = 0; j < model.size(); j++)
    {
        for (int i = 0; i < model[0].size(); i++)
        {
            cv::Vec3i sum{0, 0, 0};
            std::vector<cv::Vec3b> allValues;
            cv::Vec3b sample;
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    if (method == IM_MEAN)
                    {
                        sum += src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li);
                    }
                    if (method == IM_MEDIAN)
                    {
                        allValues.push_back(src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li));
                    }
                }
            }
            if (method == IM_MEAN)
            {
                sample = sum / (xjump * yjump); // implicit casting from Vec3i to Vec3b
            }
            if (method == IM_MEDIAN)
            {
                std::sort(allValues.begin(), allValues.end(), greaterBlue);
                sample[0] = allValues.at(allValues.size() / 2)[0];
                std::sort(allValues.begin(), allValues.end(), greaterGreen);
                sample[1] = allValues.at(allValues.size() / 2)[1];
                std::sort(allValues.begin(), allValues.end(), greaterRed);
                sample[2] = allValues.at(allValues.size() / 2)[2];
            }
            // std::cout << sample[0] << " uai";
            // model.at<Image_Region>(j, i) = Image_Region(i, j, xjump, yjump, sample, UNKNOWN);
            // std::cout << model(j, i).color; //= Image_Region();

            // std::cout << "vai" << std::endl;
            //auto* aux = new Image_Region(i,j,xjump,yjump,cv::Vec3b{0,0,0},UNKNOWN);
            // model(j, i) = Image_Region(i, j, xjump, yjump, sample, UNKNOWN);
            // model(j,i) = *aux;
            // model(j,i) = Image_Region();
            cv::Vec3b color_hsv = this->bgr_to_hsv(sample);
            //cv::Vec3b color_hsv = img_proc::bgr_to_hsv(sample);

            model[j][i] = ImageRegion(i, j, xjump, yjump, sample, color_hsv, UNKNOWN);

            label_image_segment(model[j][i], LUT);
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    if(model[j][i].label == FIELD)
                        dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = cv::Vec3b{0xf2, 0, 0xff};
                    else
                        dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = sample;
                }
            }
        }
    }
}
void Image_Segmenter::segment_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<Image_Region>>& model,
                                  int xjump, int yjump, int method)
{
    src.copyTo(dst); // TODO(Abreu): delete this line
    assert(src.rows % yjump == 0 && src.cols % xjump == 0);
    //model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump, new Image_Region());
    // model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump );
    // model = cv::Mat_<Image_Region>(src.rows/yjump, src.cols/xjump, 10);

    // note that wont work if xjump and yjump are not multipples of
    // the respective image dimensions // TODO(Abreu): add assert
    // I'll call the segmented img a "model";
    for (int j = 0; j < model.size(); j++)
    {
        for (int i = 0; i < model[0].size(); i++)
        {
            cv::Vec3i sum{0, 0, 0};
            std::vector<cv::Vec3b> allValues;
            cv::Vec3b sample;
            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    if (method == IM_MEAN)
                    {
                        sum += src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li);
                    }
                    if (method == IM_MEDIAN)
                    {
                        allValues.push_back(src.at<cv::Vec3b>(j * yjump + lj, i * xjump + li));
                    }
                }
            }
            if (method == IM_MEAN)
            {
                sample = sum / (xjump * yjump); // implicit casting from Vec3i to Vec3b
            }
            if (method == IM_MEDIAN)
            {
                std::sort(allValues.begin(), allValues.end(), greaterBlue);
                sample[0] = allValues.at(allValues.size() / 2)[0];
                std::sort(allValues.begin(), allValues.end(), greaterGreen);
                sample[1] = allValues.at(allValues.size() / 2)[1];
                std::sort(allValues.begin(), allValues.end(), greaterRed);
                sample[2] = allValues.at(allValues.size() / 2)[2];
            }
            // std::cout << sample[0] << " uai";
            // model.at<Image_Region>(j, i) = Image_Region(i, j, xjump, yjump, sample, UNKNOWN);
            // std::cout << model(j, i).color; //= Image_Region();

            // std::cout << "vai" << std::endl;
            //auto* aux = new Image_Region(i,j,xjump,yjump,cv::Vec3b{0,0,0},UNKNOWN);
            // model(j, i) = Image_Region(i, j, xjump, yjump, sample, UNKNOWN);
            // model(j,i) = *aux;
            // model(j,i) = Image_Region();
            // cv::Vec3b color_hsv = this->bgr_to_hsv(sample);
            cv::Vec3b color_hsv = img_proc::bgr_to_hsv(sample);

            model[j][i] = ImageRegion(i, j, xjump, yjump, sample, color_hsv, UNKNOWN);

            for (int li = 0; li < xjump; li++)
            {
                for (int lj = 0; lj < yjump; lj++)
                {
                    if(model[j][i].label == FIELD)
                        dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = cv::Vec3b{0xf2, 0, 0xff};
                    else
                        dst.at<cv::Vec3b>(j * yjump + lj, i * xjump + li) = sample;
                }
            }
        }
    }
}
void Image_Segmenter::label_image_segment(ImageRegion& segment, std::vector<uint8_t>& LUT)
{
    assert(LUT.size() == 256*256*256);
    // std::cout << "ai ai ai " << std::endl;
    int color = (segment.color_bgr[0] << 16) | (segment.color_bgr[1] << 8) | segment.color_bgr[2];
    assert(color < 256*256*256);
    segment.label = LUT.at(color); // using vector::at because it is safer (but quite slower) TODO(Abreu): use [] operator instead of at.
}
cv::Vec3b Image_Segmenter::bgr_to_hsv(cv::Vec3b color_bgr){
    // TODO(Abreu): find better method. http://coecsl.ece.illinois.edu/ge423/spring05/group8/finalproject/hsv_writeup.pdf , https://www.rapidtables.com/convert/color/rgb-to-hsv.html
    cv::Mat singleElement(1, 1, CV_8UC3, cv::Scalar(color_bgr[0], color_bgr[1], color_bgr[2]));
    cv::Mat hsv;
    cv::cvtColor(singleElement, hsv, CV_BGR2HSV);
    return hsv.at<cv::Vec3b>(0,0);
}

#include "ImageSegmenter.h"
#include "opencv2/core/core.hpp"
#include <exception>
#include <iostream>
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[2] < b[2]; }
} greaterRed;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[1] < b[1]; }
} greaterGreen;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[0] < b[0]; }
} greaterBlue;

ImageSegmenter::ImageSegmenter()
{

}
void ImageSegmenter::segmentImage(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<ImageRegion>> model, std::vector<uint8_t>& LUT,
                                  int xjump, int yjump, int method)
{
    src.copyTo(dst); // TODO(Abreu): delete this line
    assert(src.rows % yjump == 0 && src.cols % xjump == 0);
    //model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump, new ImageRegion());
    // model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump );
    // model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump, 10);

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
            // model.at<ImageRegion>(j, i) = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);
            // std::cout << model(j, i).color; //= ImageRegion();

            // std::cout << "vai" << std::endl;
            //auto* aux = new ImageRegion(i,j,xjump,yjump,cv::Vec3b{0,0,0},UNKNOWN);
            // model(j, i) = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);
            // model(j,i) = *aux;
            // model(j,i) = ImageRegion();
            model[j][i] = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);

            labelImageSegment(model[j][i], LUT);
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
void ImageSegmenter::segmentImage(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<ImageRegion>> model,
                                  int xjump, int yjump, int method)
{
    src.copyTo(dst); // TODO(Abreu): delete this line
    assert(src.rows % yjump == 0 && src.cols % xjump == 0);
    //model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump, new ImageRegion());
    // model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump );
    // model = cv::Mat_<ImageRegion>(src.rows/yjump, src.cols/xjump, 10);

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
            // model.at<ImageRegion>(j, i) = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);
            // std::cout << model(j, i).color; //= ImageRegion();

            // std::cout << "vai" << std::endl;
            //auto* aux = new ImageRegion(i,j,xjump,yjump,cv::Vec3b{0,0,0},UNKNOWN);
            // model(j, i) = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);
            // model(j,i) = *aux;
            // model(j,i) = ImageRegion();
            model[j][i] = ImageRegion(i, j, xjump, yjump, sample, UNKNOWN);

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
void ImageSegmenter::labelImageSegment(ImageRegion& segment, std::vector<uint8_t>& LUT)
{
    assert(LUT.size() == 256*256*256);
    // std::cout << "ai ai ai " << std::endl;
    int color = (segment.color[0] << 16) | (segment.color[1] << 8) | segment.color[2];
    assert(color < 256*256*256);
    segment.label = LUT.at(color); // using vector::at because it is safer (but quite slower) TODO(Abreu): use [] operator instead of at.
}

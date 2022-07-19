#include "Segmented_Image.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[2] < b[2]; }
} greaterRed;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[1] < b[1]; }
} greaterGreen;
struct {
    bool operator()(cv::Vec3b a, cv::Vec3b b) const { return a[0] < b[0]; }
} greaterBlue;

SegmentedImage::SegmentedImage(cv::Mat& image){
    int xjump = 5;
    int yjump = 5;
    if( image.rows%yjump != 0 || image.cols%xjump != 0){
        return;
    }
    int segmented_size_x = image.cols/xjump;
    int segmented_size_y = image.rows/yjump;

    // this->regions = new std::vector<std::vector<ImageRegion>>(
    this->regions    = new std::vector<std::vector<ImageRegion>>(
        segmented_size_y, 
        std::vector<ImageRegion>(
            segmented_size_x, 
            ImageRegion()
        )
    );
    for(int i = 0; i < segmented_size_y; i++){
        for(int j = 0; j < segmented_size_x; j++){
            int y = i*yjump;
            int x = j*xjump;
            int w = xjump;
            int h = yjump;
            // std::vector<std::vector<Image_Region>> model
            std::vector<ImageRegion>* linha = &this->regions->at(i);
            std::vector<cv::Vec3b> spots = {
                image.at<cv::Vec3b>(y,x),
                image.at<cv::Vec3b>(y,x+w),
                image.at<cv::Vec3b>(y+h,x),
                image.at<cv::Vec3b>(y+h,x+w),
                image.at<cv::Vec3b>(y+h/2,x+w/2),
            }; // TODO: use references or pointers instead of copies
            auto regionColor = bgr_median(spots);
            linha->at(j) = ImageRegion(x, y, w, h, regionColor, RegionLabel::Unknown);
            // this->regions[i][j] = ImageRegion(x, y, xjump, yjump, image.at<cv::Vec3b>(cv::Point(x,y)), RegionLabel::Unknown);
        }
    }
}
void SegmentedImage::displaySegmentedImage() const{
    int rows = this->regions->size();
    int cols = this->regions->at(0).size();
    
    int width = this->getWidth();
    int height = this->getHeight();
    cv::Mat img = Mat::zeros(height,width, CV_8UC3);
    for(const auto& line : *this->regions){
        for(const auto& region : line){
            for(int w = 0; w < region.w; w++){
                for(int h = 0; h < region.h; h++){
                    int x = region.x + w;
                    int y = region.y + h;
                    img.at<cv::Vec3b>(y, x) = region.color;
                }
            }
        }
    }
    cv::imshow("segmented", img);
}
int SegmentedImage::getHeight() const{
    auto& lastLine = this->regions->at(this->regions->size()-1);
    auto& lastRegion = lastLine.at(lastLine.size()-1);
    return lastRegion.y + lastRegion.h;
}
int SegmentedImage::getWidth() const{
    auto& lastLine = this->regions->at(this->regions->size()-1);
    auto& lastRegion = lastLine.at(lastLine.size()-1);
    return lastRegion.x + lastRegion.w;
}
cv::Vec3b SegmentedImage::bgr_median(vector<cv::Vec3b>& colors){
    cv::Vec3b sample{0,0,0};
    std::sort(colors.begin(), colors.end(), greaterBlue);
    sample[0] = colors.at(colors.size()/2+1)[0];
    std::sort(colors.begin(), colors.end(), greaterGreen);
    sample[1] = colors.at(colors.size()/2+1)[1];
    std::sort(colors.begin(), colors.end(), greaterRed);
    sample[2] = colors.at(colors.size()/2+1)[2];
    return sample;
}
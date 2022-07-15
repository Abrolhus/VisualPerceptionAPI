#include "Segmented_Image.h"
SegmentedImage::SegmentedImage(cv::Mat &image){
    int xjump = 5;
    int yjump = 5;
    int segmented_size_x = image.rows/xjump;
    int segmented_size_y = image.rows/yjump;
    this->regions = new std::vector<std::vector<Image_Region>>()
    for(int x = 0; x < image.rows; x += xjump){
        for(int y = 0; y < image.rows; y += yjump){
            this->regions[][] = image.at()
        }
    }
}
#include "Segmented_Image.h"
#include "RobotDefs.h"
#include "RelativeCoord.h"
#include <opencv2/opencv.hpp>
#include <math.h>
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

int mapFunction(int iy){
    float y = iy;
    return std::max(
        floor((y*y)/10), 
        floor(((y-1)*(y-1))/10) +1
        );
}
// 0-1 2-4 5-9 10-16 17-25
// step eh em metro o tanto que anda em y. de 0.1m em 0.1 por exemplo.
SegmentedImage::SegmentedImage(const cv::Mat& image, float y_step, int x_step, bool upper_camera){
        this->regions = new std::vector<std::vector<ImageRegion>>();
        this->width = image.cols;
        this->height = image.rows;
        cout << image.rows << ", " <<  image.cols << endl;

        float currHeadYaw = -0.0291879; // sensor.joints.angles[Joints::HeadYaw];
        float currHeadPitch = 0.00916195; //sensor.join; //sensor.joints.angles[Joints::HeadPitch];
        std::vector<int> lineYs;
        lineYs.push_back(image.rows);
        RelativeCoord rr;
        rr.fromPixel(CAM_W/2, image.rows-1, currHeadYaw, currHeadPitch, true);
        float last_x = rr.x;
        // float difference = (last_x/step -int(last_x/step) )*step; // 
        float difference = 0.0f;
        for (int j = image.rows-2; j >= 0; j--)
        {
            int i = CAM_W / 2;
            RelativeCoord rr;
            rr.fromPixel(i, j, currHeadYaw, currHeadPitch, true);
            float x, y;
            x = rr.x;
            y = rr.y;
            difference += x - last_x;
            last_x = x;
            cout << x << endl;
            if (difference <= -y_step)
            {
                lineYs.push_back(j);
                if(abs(x) >= 50 && abs(x)){
                    this->horizon = j;
                }
                // cout << x << endl;
                difference = 0.0f;
            }
        }
        cout << "ys:" << endl;
        Mat img_copy = image.clone();
        for(int ly : lineYs){
            cout << ly << ", " << endl;
            cv::line(img_copy, Point(0, ly), Point(image.cols, ly), Scalar(250, 0, 250));
        }
        imshow("vai", img_copy);

        // note que o lineYs esta de baixo pra cima

        float ySize = lineYs.size()-1;
        float xSize = image.cols/x_step;
        assert(image.cols%x_step == 0);
        this->regions = new std::vector<std::vector<ImageRegion>>(
            lineYs.size(), std::vector<ImageRegion>(xSize, ImageRegion()));

        float lastY = -1;
        int j = 0, i = 0;
        for(int j = 0; j < ySize; j++){
            for (int i = 0; i < xSize; i++)
            {
                int image_y = lineYs.at(lineYs.size() - 1 - j);
                int image_x = i * x_step;
                // cout << "(" << image_x << ", " << image_y << ")" << endl;

                int w = x_step - 1;
                int next_image_y = lineYs.at(lineYs.size() - 1 - j - 1); // next image_y
                int width = x_step;  // region width
                int height = next_image_y - image_y; // region height

                std::vector<cv::Vec3b> spots = {
                    image.at<cv::Vec3b>(image_y, image_x),
                    image.at<cv::Vec3b>(image_y, image_x + w),
                    image.at<cv::Vec3b>(next_image_y - 1, image_x),
                    image.at<cv::Vec3b>(next_image_y - 1, image_x + w),
                    // image.at<cv::Vec3b>(image_y+h/2,image_x+w/2),
                }; // TODO: use references or pointers instead of copies
                auto regionColor = bgr_median(spots);

                RegionLabel regionLabel = RegionLabel::Unknown;
                if (Field_color_detector::isField(regionColor))
                {
                    regionLabel = RegionLabel::Field;
                }
                else { 
                    regionLabel = RegionLabel::Background; 
                }
                // linha->at(j) = ImageRegion(x, y, w, h, regionColor, regionLabel);
                this->regions->at(j).at(i) = ImageRegion(image_x, image_y, width, height, regionColor, regionLabel);
                // image.at<cv::Vec3b>(cv::Point(x,y)), RegionLabel::Unknown);
            }
        }
        for (int j = 0; j < image.rows; j++){
        }
    /*
    int xjump = 10;
    // int yjump = 5;
    // if( image.rows%yjump != 0 || image.cols%xjump != 0){
      //   return;
    // }
    // int segmented_size_x = image.cols/xjump;
    // int segmented_size_y = image.rows/yjump;
    int segmented_size_x = image.cols/xjump;
    int segmented_size_y = (floor(sqrt(image.rows - 0.0001))*3.3 +1);

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
            int y = mapFunction(i);
            if(i ==0){
                y = 0;
            }
            int x = j*xjump;
            int w = xjump;
            int y2 = mapFunction(i+1);

            if(y >= image.rows){
                cout << "uaaaaaaaaaa";
                exit(1);
            }
            if(y2 >= image.rows){
                y2 = image.rows-1;
            }
            int h = y2 - y;
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

            RegionLabel regionLabel = RegionLabel::Unknown;
            if(Field_color_detector::isField(regionColor)){
                regionLabel = RegionLabel::Field;
            }
            else{
                regionLabel = RegionLabel::Background;
            }
            linha->at(j) = ImageRegion(x, y, w, h, regionColor, regionLabel);
            // this->regions[i][j] = ImageRegion(x, y, xjump, yjump, image.at<cv::Vec3b>(cv::Point(x,y)), RegionLabel::Unknown);
        }
    }
    */
}
void SegmentedImage::displaySegmentedImage() const{
    cv::Mat img(this->height,this->width, CV_8UC3);
    for(const auto& line : *this->regions){
        for(const auto& region : line){
            for(int w = 0; w < region.w; w++){
                for(int h = 0; h < region.h; h++){
                    int x = region.x + w;
                    int y = region.y + h;
                    img.at<cv::Vec3b>(y, x) = region.color;
                    if(region.label == RegionLabel::Field){
                        img.at<cv::Vec3b>(y, x) = {255,255,0};
                    }
                    if(region.label == RegionLabel::Border){
                        img.at<cv::Vec3b>(y, x) = {0,0,255};
                    }
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
void SegmentedImage::displaySegmentedImageRegions() const{
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
                    auto color = region.color;
                    if(region.label == RegionLabel::Field){
                        color = cv::Vec3b(215,50,215);
                    }
                    else if(region.label == RegionLabel::Unknown){
                        color = cv::Vec3b(0, 0, 255);
                    }
                    else if(region.label == RegionLabel::Border){
                        color = cv::Vec3b(0, 10, 250);
                    }
                    img.at<cv::Vec3b>(y, x) = color;
                }
            }
        }
    }
    cv::imshow("segmentedRegions", img);
}
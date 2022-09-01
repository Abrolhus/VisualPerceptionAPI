#include "Segmented_Image.h"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "Segmented_Image.h"
using namespace cv;
using namespace std;
const int NOT_FIELD_MAX = 5;

void scanline(SegmentedImage& segImg){
    auto border = vector<cv::Point>(segImg.regions->at(0).size());
    for(int x = 0; x < segImg.regions->at(0).size(); x++){
        unsigned int not_field_count = 0;
        for(int y = segImg.regions->size()-1; y >= 0; y--){
            auto& region = segImg.regions->at(y).at(x);
            if( region.label != RegionLabel::Field){
                not_field_count++;
                if(not_field_count > NOT_FIELD_MAX){
                    segImg.regions->at(y+NOT_FIELD_MAX).at(x).label = RegionLabel::Border;
                    border.at(x) = cv::Point(y,x);
                    break;
                }
            }
        }
    }
}
#include "field_color_detector.h"

using namespace std;
using namespace cv;

#define UPPERGREENCHROMATICITYTHRESHOLDLINES 0.43 // Valor para usar na deteccao das linhas
#define UPPERGREENCHROMATICITYTHRESHOLDFIELD 0.46 // Valor usado para deteccao do campo
#define REDCHROMATICITYTHRESHOLD0 0.37
#define LOWERGREENCHROMATICITYTHRESHOLD 0.4
#define BLUECHROMATICITYTHRESHOLD 0.38
// #define BLUECHROMATICITYTHRESHOLD 0.47

// Constructor
Field_color_detector::Field_color_detector(){}

// Destructor
Field_color_detector::~Field_color_detector(){}

float Field_color_detector::getChromaticity(uchar channelColor, Vec3b color){
    return channelColor / (float) (color[0] + color[1] + color[2]);
}

void Field_color_detector::paintField(Mat inputImg){
    Mat segmentedImg = inputImg.clone();
    for (size_t i = 0; i < inputImg.cols; i++)
    {
        for (size_t j = inputImg.rows; j > 0; j--)
        {
            auto pixelColor = inputImg.at<Vec3b>(j, i);
            if(isField(pixelColor)){
                segmentedImg.at<Vec3b>(j, i) = {255, 0, 100};
            }
        }
    }
    imshow("vai", segmentedImg);
}

bool Field_color_detector::isField(Vec3b pixel){
    // if pixel is field colored returns true
    if(getChromaticity(pixel[0], pixel) < BLUECHROMATICITYTHRESHOLD &&
       getChromaticity(pixel[1], pixel) >= UPPERGREENCHROMATICITYTHRESHOLDFIELD && 
       getChromaticity(pixel[2], pixel) < REDCHROMATICITYTHRESHOLD0){
        return true;
    }
    return false;

    // for (size_t i = 0; i < inputImg.cols; i++)
    // {
    //     for (size_t j = 0; j < inputImg.rows; j++)
    //     {
    //         auto pixelColor = inputImg.at<Vec3b>(j, i);
    //         if (getChromaticity(pixelColor[0], pixelColor) > BLUECHROMATICITYTHRESHOLD) 
    //             continue;
    //         if (getChromaticity(pixelColor[2], pixelColor) > REDCHROMATICITYTHRESHOLD0) 
    //             continue;
    //         if (getChromaticity(pixelColor[1], pixelColor) >= LOWERGREENCHROMATICITYTHRESHOLD){
    //             // if(getChromaticity(pixelColor[1], pixelColor) <= UPPERGREENCHROMATICITYTHRESHOLD)
    //             segmentedImg.at<Vec3b>(j, i) = {255, 0, 100};
    //         }
    //     }
    // }
}

// VideoCapture cap = VideoCapture(argv[1]);
// VideoWriter videoWritter = VideoWriter();
// Mat frame;
// cap >> frame;
// videoWritter.open("video.avi", CV_FOURCC('M','J','P','G'), 30, Size(frame.cols, frame.rows));
// while(cap.read(frame)){ // note que eu estou lendo o frame na condicao do while
//     for (size_t i = 0; i < frame.cols; i++) {
//         for (size_t j = 0; j < frame.rows; j++) {
//             auto pixelColor = frame.at<Vec3b>(j, i);
//             if(getChromaticity(pixelColor[0], pixelColor) > BLUECHROMATICITYTHRESHOLD)
//                 continue;
//             if(getChromaticity(pixelColor[2], pixelColor) > REDCHROMATICITYTHRESHOLD0)
//                 continue;
//             if(getChromaticity(pixelColor[1], pixelColor) >= LOWERGREENCHROMATICITYTHRESHOLD)
//                 // if(getChromaticity(pixelColor[1], pixelColor) <=
//                 UPPERGREENCHROMATICITYTHRESHOLD) frame.at<Vec3b>(j, i) = {255, 0, 100};
//         }
//     }
//     imshow("ai ai (dor)", frame);
//     videoWritter.write(frame);
//     // if(waitKey(1.0/30*1000) >= 0) break; // cada frame duraria 17ms, input do teclado para a
//     reproducao do  video
//     // if(waitKey(1.0/30*1000) >= 0) break; // cada frame duraria 17ms, input do teclado para a
//     reproducao do  video waitKey();
// }

// return 0;

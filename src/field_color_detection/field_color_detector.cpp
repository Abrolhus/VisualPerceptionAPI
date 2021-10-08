#include "field_color_detector.h"

using namespace std;
using namespace cv;

#define UPPERGREENCHROMATICITYTHRESHOLD 0.43
#define REDCHROMATICITYTHRESHOLD0 0.37
#define LOWERGREENCHROMATICITYTHRESHOLD 0.4
#define BLUECHROMATICITYTHRESHOLD 0.38
// #define BLUECHROMATICITYTHRESHOLD 0.47

// Constructor
Field_color_detector::Field_color_detector() {}

// Destructor
Field_color_detector::~Field_color_detector() {}

float Field_color_detector::getChromaticity(uchar channelColor, Vec3b color)
{
    return channelColor / (float) (color[0] + color[1] + color[2]);
}

void Field_color_detector::paintField(Mat inputImg)
{
    int cont; // Counts not green pixels in sequence

    Mat segmentedImg = inputImg.clone();
    bool paint = false;
    for (size_t i = 0; i < inputImg.cols; i += 3)
    {
        cont = 0;
        for (size_t j = inputImg.rows; j > 0; j--)
        {
            auto pixelColor = inputImg.at<Vec3b>(j, i);
            if (isField(pixelColor))
            {
                segmentedImg.at<Vec3b>(j, i) = {255, 0, 100};
                cont = 0;
            }
            else
            {
                cont++;
            }

            if (cont >= 10)
            { // Verificar valor
                break;
                // int aux; // Count greens in sequence

                // for(int z = j; z > 0; z--){
                //     pixelColor = inputImg.at<Vec3b>(j, i);
                //     if (isField(pixelColor)){
                //         aux++;
                //     } else {
                //         aux = 0;
                //     }

                //     if(aux > 5){
                //         paint = true;
                //         break;
                //     }
                // }
                // if(!paint){
                //     cont = 0;
                //     break;
                // }
            }
        }
    }
    imshow("Painted Field", segmentedImg);
}

bool Field_color_detector::isField(Vec3b pixel)
{
    if (getChromaticity(pixel[0], pixel) < BLUECHROMATICITYTHRESHOLD &&
        getChromaticity(pixel[2], pixel) < REDCHROMATICITYTHRESHOLD0 &&
        getChromaticity(pixel[1], pixel) >= LOWERGREENCHROMATICITYTHRESHOLD)
    { // Valor melhor?
        return true;
    }

    return false;
}

void Field_color_detector::paintNotField(Mat inputImg)
{
    int cont; // Counts green pixels in sequence

    Mat segmentedImg = inputImg.clone();
    bool paint = false;
    for (size_t i = 0; i < inputImg.cols; i+= 5)
    {
        cont = 0;
        for (size_t j = 0; j < inputImg.rows; j++)
        {
            auto pixelColor = inputImg.at<Vec3b>(j, i);
            if (!isField(pixelColor))
            {
                segmentedImg.at<Vec3b>(j, i) = {0, 0, 255};
                cont = 0;
            }
            else
            {
                cont++;
            }

            if (cont > 5) { break; }
        }
    }

    imshow("Painted Field", segmentedImg);
}

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
// }

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

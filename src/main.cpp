#include <ImageSegmenter/Segmented_Image.h>
#include <ImageSegmenter/field_border.h>
#include <ImageSegmenter/ransac_test.h>
#include <ImageSegmenter/RelativeCoord.h>
#include "dummy.h"
#include <file_proc/file_proc.h>
#include <img_proc/img_proc.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageSegmenter/RobotDefs.h"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
    for(int i = 1; i < argc; i++){
        Mat img_original = imread(argv[i]);
        Mat img = img_original(Rect(0,0, 320, 240));
        SegmentedImage segImg(img, 0.1f, 5, true);
        //float currHeadYaw = 0.0168321; // sensor.joints.angles[Joints::HeadYaw];
        float currHeadYaw = -0.0291879f; // sensor.joints.angles[Joints::HeadYaw];
        float currHeadPitch = 0.00916195f; //sensor.join; //sensor.joints.angles[Joints::HeadPitch];
        // SegmentedImage segmentedImage(img);
        scanline(segImg);
        Vec4d output_line;
        testLine2d(segImg, img, output_line);
        cout << "output" << output_line[0] << endl;
        segImg.displaySegmentedImage();

        // resize(img,img, Size(400,500));
        // imshow("original", img);
        GaussianBlur(img, img, Size(3, 3), 0);
        cvtColor(img, img, COLOR_BGR2HSV);
        Mat mask;
        inRange(img, Scalar(0, 0, 170), Scalar(255, 60, 255), mask);
        GaussianBlur(mask, mask, Size(3, 3), 0);
        Mat destaque;
        imshow("p&b", mask);
        Mat pEb_tiraFundo = mask.clone();
        /*
        for(int j = 0; j < pEb_tiraFundo.rows; j++){
            for(int i = 0; i < pEb_tiraFundo.cols; i++){
        }
        */
        Canny(mask, mask, 50, 200, 3);
        vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(mask, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
        for (size_t i = 0; i < linesP.size(); i++)
        {
            Vec4i l = linesP[i];
            float angle = abs(atan2(l[1] - l[3], l[0] - l[2]));
            cout << Rad2Deg(angle) << ", ";
            if((angle >= Deg2Rad(75) && angle <= Deg2Rad(105)) || (angle <= Deg2Rad(-75) && angle >= Deg2Rad(-105))){
                cout << "oi ";
                line(mask, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(110, 100, 155), 3);
            }
            else;
            // line(mask, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(110, 255, 255), 3);
        }
        line(mask, Point(output_line[0],output_line[1]), Point(output_line[2],output_line[3]), Scalar(0,0,255));
        cout << endl;
        imshow("linhas", mask);
    waitKey();
}
return 0;
}
// SensorValues sensor = readFrom(motion, sensors);

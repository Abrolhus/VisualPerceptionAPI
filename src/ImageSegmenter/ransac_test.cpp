#include"ransac_line2d.h"
#include "Segmented_Image.h"
#include "ransac_test.h"

using namespace cv;
using namespace std;

bool testLine2d(SegmentedImage& segImg, Mat& image, cv::Vec4d& output_line){
	std::vector<sac::Point2D> pCloud2D;

    for(const auto& line : *(segImg.regions)){
        for(const auto& region : line){
			if (region.label == RegionLabel::Border){
				pCloud2D.push_back(sac::Point2D(region.x, region.y));
            }
		}
	}

	sac::ransacModelLine2D line2D;
	std::vector<int> inliers;
	sac::ModelCoefficient parameter;
	line2D.setInputCloud(pCloud2D);
	line2D.setDistanceThreshold(5);
	line2D.setMaxIterations(2500);
	line2D.computeModel();
	line2D.getInliers(inliers);
	line2D.getModelCoefficients(parameter);

	Point sp((int)parameter.modelParam[0], (int)parameter.modelParam[1]);
	Point ep((int)parameter.modelParam[2], (int)parameter.modelParam[3]);
	int dx = sp.x - ep.x;
	int dy = sp.y - ep.y;
	sp.x = sp.x + 10 * dx;
	sp.y = sp.y + 10 * dy;
	ep.x = ep.x - 10 * dx;
	ep.y = ep.y - 10 * dy;

    Mat showMat = image.clone();
	line(showMat, sp, ep, Scalar(0, 0, 255), 2, 8);
    imshow("line", showMat);

	cout << "Parameter of 2D line: < " << parameter.modelParam[0] << ", " <<
		parameter.modelParam[1] << " >---< " << parameter.modelParam[2] << ", " <<
		parameter.modelParam[3] << " > " << endl;
	output_line = Vec4d{sp.x, sp.y, ep.x, ep.y};
	return true;
}
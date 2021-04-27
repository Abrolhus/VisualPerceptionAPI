#ifndef IMAGESEGMENTER_H
#define IMAGESEGMENTER_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#define UNKNOWN 0
#define FIELD 1
#define BACKGROUND 2
/** Responsible for transforming images into small matrices of Regions.
 *
 */
class imageSegmenter
{
public:
    /** Segments the image into smaller regions with the same dimensions. Each region is represented
     * by the accent color of its pixels. The resulting image is a pixelated version of the input.
     * Work in Progress
     *
     * @param[in] src[ input image
     * @param[out] dst Destination image (Debug)
     * @param[out] model matrix of regions
     * @param xjump steps in x direction
     * @param yjump steps in y direction
     */
    void segmentImage(cv::Mat& src, cv::Mat& dst, cv::Mat_<ImageRegion>& model, int xjump,
                      int yjump)
}
#endif

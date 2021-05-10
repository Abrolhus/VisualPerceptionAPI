#ifndef IMG_PROC_H
#define IMG_PROC_H
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <vector>

/** A namespace with various image processing functions.
 *
 */
namespace img_proc {
    /** Returns a rectangular region of a image.
     * Given a x,y, width and height, the function returns the corresponding part in the src image.
     * @param src Source image
     * @param roi Destination image
     * @param x X coordinate of the starting point
     * @param y Y coordinate of the starting point
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    void get_roi(cv::Mat& src, cv::Mat& roi, int x, int y, int width, int height);
    cv::Vec3b bgr_to_hsv(cv::Vec3b);
}
#endif

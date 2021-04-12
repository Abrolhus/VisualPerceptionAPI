#ifndef IMG_PROC_H
#define IMG_PROC_H
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <vector>

/** A namespace with various image processing functions.
 * A longer description of the namespace
 */
namespace img_proc {
    /** A simple sum functions.
     * Created for testing
     * @param a First number
     * @param b Second number
     * @return Sum of both numbers
     */
    int somar(int a, int b);

    /** Segments the image into smaller regions with the same dimensions. Each region is represented by the accent color of its pixels.
     * The resulting image is a pixelated version of the input.
     * Work in Progress
     *
     * @param src input image
     * @param dst Destination image (Debug)
     * @param clusters Destination matrix ("Pixelated" Image)
     * @param xjump steps in x direction
     * @param yjump steps in y direction
     */
    void clustering(cv::Mat& src, cv::Mat& dst, cv::Mat& clusters, int xjump=5, int yjump=5);
    // void simpleClustering(cv::Mat&, std::vector<unsigned short>, std::vector<cv::Vec3b> refTable);
}
#endif

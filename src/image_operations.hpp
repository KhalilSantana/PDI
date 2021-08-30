#include <opencv4/opencv2/opencv.hpp>

cv::Mat convolution(cv::Mat img, float **kernel, int kernel_size);

cv::Mat erosion (cv::Mat img, float **kernel, int kernel_size);

cv::Mat dilatation (cv::Mat img, float **kernel, int kernel_size);
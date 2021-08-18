#include <opencv4/opencv2/opencv.hpp>
#include "constants.hpp"

cv::Mat arithmetic_grayscale(cv::Mat img);

cv::Mat weighted_grayscale(cv::Mat img);

cv::Mat threshold(cv::Mat img, uchar luminance);

cv::Mat isolate_channel(cv::Mat img, int channel);
#include "constants.hpp"
#include <opencv4/opencv2/opencv.hpp>

// Create grayscale image using an arithmetic average
cv::Mat arithmetic_grayscale(cv::Mat img);

// Create grayscale image using an weighted average
cv::Mat weighted_grayscale(cv::Mat img);

cv::Mat threshold(cv::Mat img, uchar luminance);

cv::Mat add(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat sub(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat mul(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat div(cv::Mat img_lhs, cv::Mat img_rhs);

#include <opencv4/opencv2/opencv.hpp>
#include <boost/safe_numerics/checked_result.hpp>
#include <boost/safe_numerics/checked_result_operations.hpp>

cv::Mat add(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat sub(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat mul(cv::Mat img_lhs, cv::Mat img_rhs);

cv::Mat div(cv::Mat img_lhs, cv::Mat img_rhs);

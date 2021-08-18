#include "basic_operations.hpp"

cv::Mat arithmetic_grayscale(cv::Mat img) {
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    cv::Mat outputImg(width, height, CV_8UC1, cv::Scalar(0));
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            // Read inputImg pixel at (w, h)
            cv::Vec3b rgb = img.at<cv::Vec3b>(h, w);
            // Arithmetic gray
            int gray = (rgb[0] + rgb[1] + rgb[2]) / 3;
            // Write value to outputImg
            outputImg.at<uchar>(w, h) = gray;
        }
    }
    return outputImg;
}

cv::Mat weighted_grayscale(cv::Mat img) {
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    cv::Mat outputImg(width, height, CV_8UC1, cv::Scalar(0));
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            // Read inputImg pixel at (w, h)
            cv::Vec3b rgb = img.at<cv::Vec3b>(w, h);
            // Weighted airthmetic gray
            int gray = (float)rgb[0] * GRAYSCALE_RED_FACTOR;
            gray += (float)rgb[1] * GRAYSCALE_GREEN_FACTOR;
            gray += (float)rgb[2] * GRAYSCALE_BLUE_FACTOR;
            // Write value to outputImg
            outputImg.at<uchar>(h, w) = gray;
        }
    }
    return outputImg;
}

cv::Mat threshold(cv::Mat img, uchar luminance) {
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    cv::Mat outputImg(width, height, CV_8UC1, cv::Scalar(0));
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            // Read inputImg pixel at (w, h)
            uchar px = img.at<uchar>(w, h);
            if (px < luminance) {
                px = 0;
            } else {
                px = 255;
            }
            // Write value to outputImg
            outputImg.at<uchar>(h, w) = px;
        }
    }
    return outputImg;
}
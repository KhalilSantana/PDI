#include "basic_operations.hpp"

cv::Mat arithmetic_grayscale(cv::Mat img) {
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int h = 0; h < img.rows; h++) {
        for (int w = 0; w < img.cols; w++) {
            // Read inputImg pixel at (w, h)
            cv::Vec3b rgb = img.at<cv::Vec3b>(h, w);
            // Arithmetic gray
            int gray = (rgb[0] + rgb[1] + rgb[2]) / 3;
            // Write value to outputImg
            outputImg.at<uchar>(h, w) = gray;
        }
    }
    return outputImg;
}

cv::Mat weighted_grayscale(cv::Mat img) {
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int h = 0; h < img.rows; h++) {
        for (int w = 0; w < img.cols; w++) {
            // Read inputImg pixel at (w, h)
            cv::Vec3b rgb = img.at<cv::Vec3b>(h, w);
            // Weighted airthmetic gray
            // NOTE: OpenCV uses BGR by default, so channel=0 is BLUE
            int gray = (float)rgb[2] * GRAYSCALE_RED_FACTOR;
            gray += (float)rgb[1] * GRAYSCALE_GREEN_FACTOR;
            gray += (float)rgb[0] * GRAYSCALE_BLUE_FACTOR;
            // Write value to outputImg
            outputImg.at<uchar>(h, w) = gray;
        }
    }
    return outputImg;
}

cv::Mat threshold(cv::Mat img, uchar luminance) {
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int h = 0; h < img.rows; h++) {
        for (int w = 0; w < img.cols; w++) {
            // Read inputImg pixel at (h, w)
            uchar px = img.at<uchar>(h, w);
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

cv::Mat isolate_channel(cv::Mat img, int channel) {
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int h = 0; h < img.rows; h++) {
        for (int w = 0; w < img.cols; w++) {
            // Read inputImg pixel at (h, w)
            cv::Vec3b px = cv::Vec3b(0, 0, 0);
            // NOTE: OpenCV uses BGR by default, so channel=0 is BLUE
            px[channel] = img.at<cv::Vec3b>(h, w)[channel];
            outputImg.at<cv::Vec3b>(h, w) = px;
        }
    }
    return outputImg;
}
#include "include/image_arithmatic.hpp"

cv::Mat add(cv::Mat img_lhs, cv::Mat img_rhs) {
    cv::Mat outputImg(img_lhs.rows, img_lhs.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int h = 0; h < img_lhs.rows; h++) {     // height
        for (int w = 0; w < img_lhs.cols; w++) { // width
            // Read inputImg pixel at (w, h)
            cv::Vec3b px_lhs = img_lhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px_rhs = img_rhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px;
            for (int i = 0; i < 3; i++) {
                int px_val = px_lhs[i] + px_rhs[i];
                // TODO: This is ugly and might not work for 100% of the cases
                // Figure out how to use a checked arithmetic module from boost
                if (px_val > 255) {
                    px_val = 255;
                }
                //
                px[i] = px_val;
                // printf("[channel: %d] %d - %d = %d\n", i, px_lhs[i],
                // px_rhs[i], px[i]);
            }
            // Write value to outputImg
            outputImg.at<cv::Vec3b>(h, w) = px;
        }
    }
    return outputImg;
}

cv::Mat sub(cv::Mat img_lhs, cv::Mat img_rhs) {
    cv::Mat outputImg(img_lhs.rows, img_lhs.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int h = 0; h < img_lhs.rows; h++) {     // height
        for (int w = 0; w < img_lhs.cols; w++) { // width
            // Read inputImg pixel at (w, h)
            cv::Vec3b px_lhs = img_lhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px_rhs = img_rhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px;
            for (int i = 0; i < 3; i++) {
                int px_val = px_lhs[i] - px_rhs[i];
                // TODO: This is ugly and might not work for 100% of the cases
                // Figure out how to use a checked arithmetic module from boost
                if (px_val < 0) {
                    px_val = 0;
                }
                //
                px[i] = px_val;
                // printf("[channel: %d] %d - %d = %d\n", i, px_lhs[i],
                // px_rhs[i], px[i]);
            }
            // Write value to outputImg
            outputImg.at<cv::Vec3b>(h, w) = px;
        }
    }
    return outputImg;
}

cv::Mat mul(cv::Mat img_lhs, cv::Mat img_rhs) {
    cv::Mat outputImg(img_lhs.rows, img_lhs.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int h = 0; h < img_lhs.rows; h++) {     // height
        for (int w = 0; w < img_lhs.cols; w++) { // width
            // Read inputImg pixel at (w, h)
            cv::Vec3b px_lhs = img_lhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px_rhs = img_rhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px;
            for (int i = 0; i < 3; i++) {
                int px_val = px_lhs[i] * px_rhs[i];
                // TODO: This is ugly and might not work for 100% of the cases
                // Figure out how to use a checked arithmetic module from boost
                if (px_val > 255) {
                    px_val = 255;
                }
                //
                px[i] = px_val;
                // printf("[channel: %d] %d * %d = %d\n", i, px_lhs[i],
                // px_rhs[i], px[i]);
            }
            // Write value to outputImg
            outputImg.at<cv::Vec3b>(h, w) = px;
        }
    }
    return outputImg;
}

cv::Mat div(cv::Mat img_lhs, cv::Mat img_rhs) {
    cv::Mat outputImg(img_lhs.rows, img_lhs.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int h = 0; h < img_lhs.rows; h++) {     // height
        for (int w = 0; w < img_lhs.cols; w++) { // width
            // Read inputImg pixel at (w, h)
            cv::Vec3b px_lhs = img_lhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px_rhs = img_rhs.at<cv::Vec3b>(h, w);
            cv::Vec3b px;
            for (int i = 0; i < 3; i++) {
                if (px_rhs[i] == 0) {
                    px[i] = 255;
                    continue;
                }
                px[i] = px_lhs[i] / px_rhs[i];
            }
            // Write value to outputImg
            outputImg.at<cv::Vec3b>(h, w) = px;
        }
    }
    return outputImg;
}

cv::Mat subBin(cv::Mat img_lhs, cv::Mat img_rhs) {
    cv::Size size = img_lhs.size();
    int width = size.width;
    int height = size.height;
    cv::Mat outputImg(height, width, CV_8UC1, cv::Scalar(0));
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            // Read inputImg pixel at (w, h)
            uchar px_lhs = img_lhs.at<uchar>(h, w);
            uchar px_rhs = img_rhs.at<uchar>(h, w);
            uchar px;
            int px_val = px_lhs - px_rhs;
            // TODO: This is ugly and might not work for 100% of the cases
            // Figure out how to use a checked arithmetic module from boost
            if (px_val < 0) {
                px_val = 0;
            }
            //
            px = px_val;
            // printf("[channel: %d] %d - %d = %d\n", i, px_lhs[i], px_rhs[i],
            // px[i]);
            // Write value to outputImg
            outputImg.at<uchar>(h, w) = px;
        }
    }
    return outputImg;
}
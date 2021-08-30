#include "include/image_operations.hpp"

cv::Mat convolution(cv::Mat img, float **kernel, int kernel_size) {
    int kernel_center = kernel_size / 2;
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(1));
    for (int r = kernel_center; r < img.rows - kernel_center; r++) {
        for (int c = kernel_center; c < img.cols - kernel_center; c++) {
            int px = 0; // new outputImg pixel.
            for (int j = -kernel_center; j < kernel_size - 1; j++) {
                for (int k = -kernel_center; k < kernel_size - 1; k++) {
                    /* Representation of target image with a 3x3 kernel.
                        *** j = k = -1 in first iteration.

                        (c-1, r-1), (c-1, r), (c-1, r+1),
                        (c, r-1),   (c, r),     (c, r+1),
                        (c+1, r-1), (c+1, r), (c+1, r+1),
                    */

                    int posX = r + j;
                    int posY = c + k;
                    // get the pixel value
                    px += img.at<uchar>(posX, posY) *
                          kernel[j + kernel_center][k + kernel_center];
                }
            }
            // Write value to outputImg image
            outputImg.at<uchar>(r, c) = px < 0 ? 0 : px > 255 ? 255 : px;
        }
    }
    return outputImg;
}

cv::Mat erosion(cv::Mat img, float **kernel, int kernel_size) {
    int kernel_center = kernel_size / 2;
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int c = kernel_center; c < img.cols - kernel_center; c++) {
        for (int r = kernel_center; r < img.rows - kernel_center; r++) {
            int px = 1; // new outputImg pixel.
            for (int j = -kernel_center; j < kernel_size - 1;
                 j++) { // for each kernel row
                for (int k = -kernel_center; k < kernel_size - 1;
                     k++) { // for each kernel column
                    // get kernel pixel in current iteration
                    float kernel_cell =
                        kernel[j + kernel_center][k + kernel_center];
                    int posX = c + j;
                    int posY = r + k;
                    // check if img need to be changed.
                    if (kernel_cell == 0)
                        continue;
                    if ((img.at<uchar>(posY, posX) == 0)) {
                        px = 0;
                        break;
                    }
                }
            }
            // Write value to outputImg image
            outputImg.at<uchar>(r, c) = px == 0 ? 0 : 255;
        }
    }
    return outputImg;
}

cv::Mat dilatation(cv::Mat img, float **kernel, int kernel_size) {
    int kernel_center = kernel_size / 2;
    cv::Mat outputImg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
    for (int c = kernel_center; c < img.cols - kernel_center; c++) {
        for (int r = kernel_center; r < img.rows - kernel_center; r++) {
            // check if img need to be changed.
            if (img.at<uchar>(r, c) == 0 ||
                kernel[kernel_center][kernel_center] == 0)
                continue;
            for (int j = -kernel_center; j < kernel_size - 1;
                 j++) { // for each kernel row
                for (int k = -kernel_center; k < kernel_size - 1;
                     k++) { // for each kernel column
                    float kernel_cell =
                        kernel[j + kernel_center][k + kernel_center];
                    // check if img need to be changed.
                    if (kernel_cell == 0)
                        continue;
                    int posX = c + j;
                    int posY = r + k;
                    // change img
                    outputImg.at<uchar>(posY, posX) = 255;
                }
            }
        }
    }
    return outputImg;
}

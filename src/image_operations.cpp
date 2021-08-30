#include "image_operations.hpp"

cv::Mat convolution(cv::Mat img, float **kernel, int kernel_size) {
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    cv::Mat outputImg(height, width, CV_8UC1, cv::Scalar(0));
    // apply convolution matrix kernel in img
    for (int c = 0; c < width; c++) {      // for each column
        for (int r = 0; r < height; r++) { // for each row
            uchar px = 0;                      // new outputImg pixel.
            int kernel_center = kernel_size / 2;
            for (int j = -kernel_center; j < kernel_size - 1;
                 j++) { // for each kernel row
                for (int k = -kernel_center; k < kernel_size - 1;
                     k++) { // for each kernel column
                    // get the pixel that need to be changed
                    /* Representation of target image with a 3x3 kernel.
                        (c-1, r-1), (c-1, r), (c-1, r+1),
                        (c, r-1),   (c, r),     (c, r+1),
                        (c+1, r-1), (c+1, r), (c+1, r+1),
                    */
                    int posX = c + j;
                    int posY = r + k;
                    // check if the pixel is in the image
                    posX < 0        ? posX = 0
                    : posX >= width ? posX = width - 1
                                    : posX;
                    posY < 0         ? posY = 0
                    : posY >= height ? posY = height - 1
                                     : posY;
                    // get the pixel value
                    px += img.at<uchar>(posY, posX) *
                              kernel[j + kernel_center][k + kernel_center];
                }
            }
            // Write value to outputImg image
            outputImg.at<uchar>(r, c) = px<0 ? px = 0 : px> 255 ? px = 255 : px;
        }
    }
    return outputImg;
}

cv::Mat erosion(cv::Mat img, float **kernel, int kernel_size) {
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    int kernel_center = kernel_size / 2;
    cv::Mat outputImg(height, width, CV_8UC1, cv::Scalar(0));
    for (int c = kernel_center; c < width-kernel_center; c++) {      // for each column
        for (int r = kernel_center; r < height-kernel_center; r++) { // for each row
            uchar px = 1;                      // new outputImg pixel.
            for (int j = -kernel_center; j < kernel_size - 1; j++) { // for each kernel row
                for (int k = -kernel_center; k < kernel_size - 1; k++) { // for each kernel column
                    float kernel_cell =
                        kernel[j + kernel_center][k + kernel_center];
                    int posX = c + j;
                    int posY = r + k;
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
    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    int kernel_center = kernel_size / 2;
    cv::Mat outputImg(height, width, CV_8UC1, cv::Scalar(0));
    for (int c = kernel_center; c < width-kernel_center; c++) {      // for each column
        for (int r = kernel_center; r < height-kernel_center; r++) { // for each row
            uchar px = 1;                      // new outputImg pixel.
            if(img.at<uchar>(r, c) == 0 || kernel[kernel_center][kernel_center] == 0)continue;
            for (int j = -kernel_center; j < kernel_size - 1; j++) { // for each kernel row
                for (int k = -kernel_center; k < kernel_size - 1; k++) { // for each kernel column
                    float kernel_cell = kernel[j + kernel_center][k + kernel_center];
                    if(kernel_cell==0) continue;
                    int posX = c + j;
                    int posY = r + k;
                    // check if the pixel is in the image
                    outputImg.at<uchar>(posY, posX) = 255;
                }
            }
        }
    }
    return outputImg;
}




#include "image_operations.hpp"

cv::Mat convmatrix(cv::Mat img, float kernel[][3]) {
    // printf("Convolving image with kernel\n");

    cv::Size size = img.size();
    int width = size.width;
    int height = size.height;
    printf("%d, %d", width, height);
    //result image
    cv::Mat result(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    // kernel filters:
    float mask[3][3] = {
            {0 - 1, 0},
            {-1, 5, -1},
            {0, -1, 0},
        };
    float bottomSobel[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1},
    };
    //set kernel filter
    kernel = bottomSobel;

    // apply convolution matrix kernel in img
    for (int c = 0; c < width; c++) { // for each column
        for (int r = 0; r < height; r++) { // for each row
            cv::Vec3b px; // new result pixel.
            for (int i = 0; i < 3; i++) { // for each channel
                float px_val = 0; // new pixel_channel value
                for (int j = 0; j < 3; j++) { // for each kernel row
                    for (int k = 0; k < 3; k++) { // for each kernel column
                        // get the pixel that need to be changed
                        /* Representation of target image.
                            (j-1, k-1), (j-1, k), (j-1, k+1)
                            (j, k-1),   (j, k),   (j, k+1),
                            (j+1, k-1), (j+1, k), (j+1, k+1)   
                        */
                        int posX = j-1 + c;
                        int posY = k-1 + r;
                        // check if the pixel is in the image
                        posX<0 ? posX=0 : posX>=width ? posX=width-1 : posX;
                        posY<0 ? posY=0 : posY>=height ? posY=height-1 : posY;
                        // get the pixel value 
                        px_val += img.at<cv::Vec3b>(posY, posX)[i] * kernel[j][k];
                    }
                }
                //threshold the pixel value
                px_val<0 ? px_val=0 : px_val>255 ? px_val=255 : px_val;
                px[i] = px_val;
            }
            // Write value to result image
            result.at<cv::Vec3b>(r, c) = px;
        }
    }
    return result;
}
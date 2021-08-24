#include "image_arithmatic.hpp"
#include "basic_operations.hpp"
#include "image_operations.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main(int argc, char **argv) {
    // if (argc != 3) {
    //     printf("usage: %s <Image_Path>\n", argv[0]);
    //     return -1;
    // }
    Mat image, image2;
    image = imread(argv[1], 1);
    // image2 = imread(argv[2], 1);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    const int channels = image.channels();
    printf("Number of channels = %d\n", channels);
    // Mat output = threshold(weighted_grayscale(image),150);
    //conv matrix with image and empty cv::Mat
    float kernel[3][3];
    Mat output = convmatrix(image, kernel);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", output);
    waitKey(0);
    return 0;
}

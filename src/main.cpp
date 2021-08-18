#include "image_arithmatic.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image, image2;
    image = imread(argv[1], 1);
    image2 = imread(argv[2], 1);
    if (!image.data || !image2.data) {
        printf("No image data \n");
        return -1;
    }
    const int channels = image.channels();
    printf("Number of channels = %d\n", channels);
    Mat output = sub(image, image2);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", output);
    waitKey(0);
    return 0;
}

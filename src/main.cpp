#include "image_arithmatic.hpp"
#include "basic_operations.hpp"
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
    image2 = imread(argv[2], 1);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    // Arithmetic operations
    Mat addImg = add(image, image2);
    Mat subImg = sub(image, image2);
    Mat mulImg = mul(image, image2);
    Mat divImg = div(image, image2);
    imwrite("output/add.png", addImg);
    imwrite("output/sub.png", subImg);
    imwrite("output/mul.png", mulImg);
    imwrite("output/div.png", divImg);
    // // Basic operations
    Mat arithGrayImg = arithmetic_grayscale(image);
    Mat weightedGrayImg = weighted_grayscale(image);
    Mat threshImg = threshold(weightedGrayImg, 150);
    Mat redImg = isolate_channel(image, 2);
    Mat greenImg = isolate_channel(image, 1);
    Mat blueImg = isolate_channel(image, 0);
    imwrite("output/arith-grayscale.png", arithGrayImg);
    imwrite("output/weigh-grayscale.png", weightedGrayImg);
    imwrite("output/threshold.png", threshImg);
    imwrite("output/red-channel.png", redImg);
    imwrite("output/green-channel.png", greenImg);
    imwrite("output/blue-channel.png", blueImg);
    // namedWindow("Display Image", WINDOW_AUTOSIZE);
    // imshow("Display Image", output);
    // waitKey(0);
    // destroyWindow("Display Image");
    return 0;
}

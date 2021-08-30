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
    image = imread(argv[1] ? argv[1] : "ubuntu.png", 1);
    image2 = imread(argv[2] ? argv[2] :"ubuntu.png", 1);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    // Arithmetic operations
    // Mat addImg = add(image, image2);
    // Mat subImg = sub(image, image2);
    // Mat mulImg = mul(image, image2);
    // Mat divImg = div(image, image2);
    // imwrite("output/add.png", addImg);
    // imwrite("output/sub.png", subImg);
    // imwrite("output/mul.png", mulImg);
    // imwrite("output/div.png", divImg);
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

    float sharpen[3][3] = {
        {0 - 1, 0},
        {-1, 5, -1},
        {0, -1, 0},
    };
    float bottomSobel[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };
    float blur[3][3] = {
        {0.0625, 0.125, 0.0625},
        {0.125, 0.25, 0.125},
        {0.0625, 0.125, 0.0625}
    };
    float mfe[3][3] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    float mfd[3][3] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };

       const int size = 3;
    float *kernel[size];
 
    for(int i = 0; i <size; i++)
        kernel[i] = bottomSobel[i];

    Mat convolutedImg = convolution(threshImg, kernel, size);
    imwrite("output/convolution.png", convolutedImg);
     
    for(int i = 0; i <size; i++)
        kernel[i] = mfe[i];

    Mat erodedImg = erosion(threshImg, kernel, size);
    imwrite("output/Erosion.png", erodedImg);
     
    for(int i = 0; i <size; i++)
        kernel[i] = mfd[i];

    Mat dilatedImg = dilatation(threshImg, kernel, size);
    imwrite("output/Dilation.png", dilatedImg);

    // Mat boundExt = sub(dilatedImg, threshImg);
    // imwrite("output/boundary-extraction.png", boundExt);
    // namedWindow("Display Image", WINDOW_AUTOSIZE);
    // imshow("Display Image", output);
    // waitKey(0);
    // destroyWindow("Display Image");
    return 0;
}

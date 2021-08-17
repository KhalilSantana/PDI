#include <stdio.h>
#include "opencv4/opencv2/opencv.hpp"
using namespace cv;

Mat arithmetic_grayscale(Mat img) {
	cv::Size size = img.size();
	int width = size.width;
	int height = size.height;
	Mat outputImg(width, height, CV_8UC1, Scalar(0));
	for (int w=0; w<width; w++) {
		for (int h=0; h<height; h++) {
		   // Read inputImg pixel at (w, h)
		   Vec3b rgb = img.at<Vec3b>(w, h);
		   // Arithmetic gray
		   int gray = (rgb[0] + rgb[1] + rgb[2])/3;
		   // Write value to outputImg
		   outputImg.at<uchar>(Point(w, h)) = gray;
		}
	}
	return outputImg;
}

int main(int argc, char** argv ) {
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    const int channels = image.channels();
    printf("Number of channels = %d\n", channels);
    Mat arith_gray = arithmetic_grayscale(image);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", arith_gray);
    waitKey(0);
    return 0;
}



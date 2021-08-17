#include <stdio.h>
#include "opencv4/opencv2/opencv.hpp"
using namespace cv;

const double GRAYSCALE_RED_FACTOR   = 0.299;
const double GRAYSCALE_GREEN_FACTOR = 0.587;
const double GRAYSCALE_BLUE_FACTOR  = 0.114;

Mat arithmetic_grayscale(Mat img) {
	cv::Size size = img.size();
	int width = size.width;
	int height = size.height;
	Mat outputImg(width, height, CV_8UC1, Scalar(0));
	for (int w=0; w<width; w++) {
		for (int h=0; h<height; h++) {
		   // Read inputImg pixel at (w, h)
		   Vec3b rgb = img.at<Vec3b>(h, w);
		   // Arithmetic gray
		   int gray = (rgb[0] + rgb[1] + rgb[2])/3;
		   // Write value to outputImg
		   outputImg.at<uchar>(Point(w, h)) = gray;
		}
	}
	return outputImg;
}

Mat weighted_grayscale(Mat img) {
	cv::Size size = img.size();
	int width = size.width;
	int height = size.height;
	Mat outputImg(width, height, CV_8UC1, Scalar(0));
	for (int w=0; w<width; w++) {
		for (int h=0; h<height; h++) {
		   // Read inputImg pixel at (w, h)
		   Vec3b rgb = img.at<Vec3b>(w, h);
		   // Weighted airthmetic gray
		   int gray =  (float)rgb[0] * GRAYSCALE_RED_FACTOR;
		   gray += (float)rgb[1] * GRAYSCALE_GREEN_FACTOR;
		   gray += (float)rgb[2] * GRAYSCALE_BLUE_FACTOR;
		   // Write value to outputImg
		   outputImg.at<uchar>(Point(h, w)) = gray;
		}
	}
	return outputImg;
}

Mat threshold(Mat img, uchar luminance) {
	cv::Size size = img.size();
	int width = size.width;
	int height = size.height;
	Mat outputImg(width, height, CV_8UC1, Scalar(0));
	for (int w=0; w<width; w++) {
		for (int h=0; h<height; h++) {
		   // Read inputImg pixel at (w, h)
		   uchar px = img.at<uchar>(w, h);
		   if (px < luminance) {
			   px = 0;
		   } else {
			   px = 255;
		   }
		   // Write value to outputImg
		   outputImg.at<uchar>(Point(h, w)) = px;
		}
	}
	return outputImg;
}

Mat sub(Mat img_lhs, Mat img_rhs) {
        cv::Size size = img_lhs.size();
        int width = size.width;
        int height = size.height;
        Mat outputImg(width, height, CV_8UC3, Scalar(0, 0, 0));
        for (int w=0; w<width; w++) {
                for (int h=0; h<height; h++) {
                   // Read inputImg pixel at (w, h)
                   Vec3b px_lhs = img_lhs.at<Vec3b>(w, h);
                   Vec3b px_rhs = img_rhs.at<Vec3b>(w, h);
                   Vec3b px;
		   for (int i=0; i<3; i++) {
			   px[i] = px_lhs[i] - px_rhs[i];
		   }
                  // Write value to outputImg
                   outputImg.at<Vec3b>(Point(h, w)) = px;
                }
        }
        return outputImg;
}

Mat add(Mat img_lhs, Mat img_rhs) {
        cv::Size size = img_lhs.size();
        int width = size.width;
        int height = size.height;
        Mat outputImg(width, height, CV_8UC3, Scalar(0, 0, 0));
        for (int w=0; w<width; w++) {
                for (int h=0; h<height; h++) {
                   // Read inputImg pixel at (w, h)
                   Vec3b px_lhs = img_lhs.at<Vec3b>(w, h);
                   Vec3b px_rhs = img_rhs.at<Vec3b>(w, h);
                   Vec3b px;
		   for (int i=0; i<3; i++) {
			   px[i] = px_lhs[i] + px_rhs[i];
		   }
                  // Write value to outputImg
                   outputImg.at<Vec3b>(Point(h, w)) = px;
                }
        }
        return outputImg;
}

Mat div(Mat img_lhs, Mat img_rhs) {
        cv::Size size = img_lhs.size();
        int width = size.width;
        int height = size.height;
        Mat outputImg(width, height, CV_8UC3, Scalar(0, 0, 0));
        for (int w=0; w<width; w++) {
                for (int h=0; h<height; h++) {
                   // Read inputImg pixel at (w, h)
                   Vec3b px_lhs = img_lhs.at<Vec3b>(w, h);
                   Vec3b px_rhs = img_rhs.at<Vec3b>(w, h);
                   Vec3b px;
		   for (int i=0; i<3; i++) {
			   px[i] = px_lhs[i] / px_rhs[i];
		   }
                  // Write value to outputImg
                   outputImg.at<Vec3b>(Point(h, w)) = px;
                }
        }
        return outputImg;
}

Mat mul(Mat img_lhs, Mat img_rhs) {
        cv::Size size = img_lhs.size();
        int width = size.width;
        int height = size.height;
        Mat outputImg(width, height, CV_8UC3, Scalar(0, 0, 0));
        for (int w=0; w<width; w++) {
                for (int h=0; h<height; h++) {
                   // Read inputImg pixel at (w, h)
                   Vec3b px_lhs = img_lhs.at<Vec3b>(w, h);
                   Vec3b px_rhs = img_rhs.at<Vec3b>(w, h);
                   Vec3b px;
		   for (int i=0; i<3; i++) {
			   px[i] = px_lhs[i] * px_rhs[i];
		   }
                  // Write value to outputImg
                   outputImg.at<Vec3b>(Point(h, w)) = px;
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
    Mat output = sub(image, threshold(arithmetic_grayscale(image, 200)));
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", output);
    waitKey(0);
    return 0;
}



#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

#include<iostream>

using namespace std;

using namespace cv;

int main()

{

	Mat image = Mat::zeros(300, 600, CV_8UC3);

	circle(image, Point(300, 200), 100, Scalar(25, 110, 288), -100);

	circle(image, Point(400, 200), 100, Scalar(255, 123, 127), -100);

	imshow("Show Window", image);

	waitKey(0);

	return 0;

}
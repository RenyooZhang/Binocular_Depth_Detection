#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include "calibration.h"
#include "ExCalibration.h"
#include "undistort.h"

using namespace std;
using namespace cv;

int main()
{
    string patternImgPath = "data/pattern/";            // 内参提取图像
    string calibResultPath = "data/results/";           // 内参存放地址
    string srcImgPath1 = "data/srcImg/test1.jpg";           // 矫正的原始图片
    string srcImgPath2 = "data/srcImg/test2.jpg";
    Mat corrected_image1 = imread(srcImgPath1);         // 声明校正后的图像
    Mat corrected_image2 = imread(srcImgPath2);
    Size boardSize = Size(9, 6);

    // 相机内参计算
    CCalibration calibration(patternImgPath, calibResultPath, boardSize);
    calibration.run();

    // 畸变矫正
    CUndistort undistort1(srcImgPath1, calibResultPath);
    undistort1.run(corrected_image1);
    CUndistort undistort2(srcImgPath2, calibResultPath);
    undistort2.run(corrected_image2);

    // 显示校正后的图像
    cv::namedWindow("show", 1);
    imshow("show", corrected_image1);
    waitKey(0);                                         // 等待键盘敲击
    cv::namedWindow("show", 2);
    imshow("show", corrected_image2);
    waitKey(0);

    // 光流法提取匹配特征点
    Mat R, t;
    ExCalibration ex_calibration(corrected_image1, corrected_image2, calibResultPath);
    ex_calibration.GetRt(R, t);
    return 0;
}

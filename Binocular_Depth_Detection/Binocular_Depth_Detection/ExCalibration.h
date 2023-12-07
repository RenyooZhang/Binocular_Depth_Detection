#pragma once
#include "opencv2\opencv.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

#define CV
//#define FISHEYE

class ExCalibration
{
public:
    ExCalibration(Mat Corrected_image1, Mat Corrected_image2, string CalibResultPath)
    {
        this->Corrected_image1 = Corrected_image1;
        this->Corrected_image2 = Corrected_image2;
        this->calibResultPath = CalibResultPath;
        this->camK = Mat::eye(Size(3, 3), CV_32FC1);
    }
    ~ExCalibration() {}

private:
    Mat Corrected_image1;
    Mat Corrected_image2;
    string calibResultPath;
    Mat camK;
    std::vector<cv::Point2f> m_pts1, m_pts2;
    Mat m_R;
    Mat m_t;
private:
    bool writeParams();
    void Getpts();
    void RunRt();
public:
    void GetRt(Mat& R, Mat& t);
};
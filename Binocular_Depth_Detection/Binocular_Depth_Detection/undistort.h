#include "opencv2\opencv.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include "calibration.h"
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

class CUndistort
{
public:
    CUndistort(string srcImgPath, string calibResultPath)
    {
        this->srcImgPath=srcImgPath;
        this->calibResultPath=calibResultPath;
        this->K=Mat::eye(Size(3, 3), CV_32FC1);
        this->discoeff=Mat::zeros(Size(1, 5), CV_32FC1); // 这个地方CV是Size(1, 5)，FISHEYE是Size(1, 4)
    }
    ~CUndistort(){}

private:
    string srcImgPath;
    string calibResultPath;
    vector<Mat> srcImgList;
    vector<Mat> dsrImgList;
    Mat K;
    Mat R;
    Mat discoeff;

public:
    bool readParams();
    bool undistProcess();
    void run();

};

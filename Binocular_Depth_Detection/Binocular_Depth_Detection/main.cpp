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
    string patternImgPath = "data/pattern/";            // �ڲ���ȡͼ��
    string calibResultPath = "data/results/";           // �ڲδ�ŵ�ַ
    string srcImgPath1 = "data/srcImg/test1.jpg";           // ������ԭʼͼƬ
    string srcImgPath2 = "data/srcImg/test2.jpg";
    Mat corrected_image1 = imread(srcImgPath1);         // ����У�����ͼ��
    Mat corrected_image2 = imread(srcImgPath2);
    Size boardSize = Size(9, 6);

    // ����ڲμ���
    CCalibration calibration(patternImgPath, calibResultPath, boardSize);
    calibration.run();

    // �������
    CUndistort undistort1(srcImgPath1, calibResultPath);
    undistort1.run(corrected_image1);
    CUndistort undistort2(srcImgPath2, calibResultPath);
    undistort2.run(corrected_image2);

    // ��ʾУ�����ͼ��
    cv::namedWindow("show", 1);
    imshow("show", corrected_image1);
    waitKey(0);                                         // �ȴ������û�
    cv::namedWindow("show", 2);
    imshow("show", corrected_image2);
    waitKey(0);

    // ��������ȡƥ��������
    Mat R, t;
    ExCalibration ex_calibration(corrected_image1, corrected_image2, calibResultPath);
    ex_calibration.GetRt(R, t);
    return 0;
}

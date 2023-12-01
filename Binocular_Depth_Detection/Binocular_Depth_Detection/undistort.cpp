#include "undistort.h"

bool CUndistort::readParams()
{
    ifstream in;
    float a[9] = { 0 };
    in.open(calibResultPath+"calibResult.txt", ios::in);
    //in >> a[0];
    //in >> a[1];
    //in >> a[2];
    //in >> a[3];
    in >> K.at<float>(0, 0);
    in >> K.at<float>(1, 1);
    in >> K.at<float>(0, 2);
    in >> K.at<float>(1, 2);
#ifdef CV
    //in >> a[4];
    //in >> a[5];
    //in >> a[6];
    //in >> a[7];
    //in >> a[8];
	in >> discoeff.at<float>(0, 0);
	in >> discoeff.at<float>(1, 0);
	in >> discoeff.at<float>(2, 0);
	in >> discoeff.at<float>(3, 0);
	in >> discoeff.at<float>(4, 0);
    //discoeff.at<float>(0, 0) /= 20;
    //discoeff.at<float>(1, 0) /= 20;
    //discoeff.at<float>(2, 0) /= 20;
    //discoeff.at<float>(3, 0) /= 20;
    //discoeff.at<float>(4, 0) /= 20;
#elif defined FISHEYE
	in >> discoeff.at<float>(0, 0);
	in >> discoeff.at<float>(1, 0);
	in >> discoeff.at<float>(2, 0);
	in >> discoeff.at<float>(3, 0);
#endif
    in.close();
    return true;
}

bool CUndistort::undistProcess()
{
    //***************»û±äÐ£Õý****************//
    R=Mat::eye(Size(3, 3),CV_32FC1);
    Mat mapx, mapy;
    Mat srcImg=imread(srcImgPath);
    Mat dstImg;
#ifdef CV
    cv::initUndistortRectifyMap(K, discoeff, R, K, srcImg.size(),CV_32FC1, mapx, mapy);
#elif defined FISHEYE
	cv::fisheye::initUndistortRectifyMap(K, discoeff,R, K, srcImg.size(), CV_32FC1, mapx, mapy);
#endif
    remap(srcImg, dstImg, mapx, mapy, CV_INTER_LINEAR);
	cv::resize(dstImg, dstImg, cv::Size(), 0.25, 0.25, CV_INTER_LINEAR);
	cv::namedWindow("show", 1);
    imshow("show", dstImg);
    waitKey(0);

    return true;
}

void CUndistort::run()
{
    bool readSuccess=readParams();
	if (!readSuccess)
	{
		cout << "read Params Failed!" << endl;
		getchar();
	}
    undistProcess();
}


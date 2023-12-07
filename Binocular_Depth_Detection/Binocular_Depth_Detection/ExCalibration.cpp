#include "ExCalibration.h"

bool ExCalibration::writeParams()
{
    ifstream in;
    in.open(calibResultPath + "calibResult.txt", ios::in);
    in >> camK.at<float>(0, 0);
    in >> camK.at<float>(1, 1);
    in >> camK.at<float>(0, 2);
    in >> camK.at<float>(1, 2);
    return true;
}

void ExCalibration::Getpts() {
    Mat distortedImg1 = Corrected_image1; // ���ػ���У�����ͼ��1
    Mat distortedImg2 = Corrected_image2; // ���ػ���У�����ͼ��2

    if (distortedImg1.empty() || distortedImg2.empty()) {
        cout << "Error: Unable to load images!" << endl;
        return;
    }

    Mat gray1, gray2;
    cvtColor(distortedImg1, gray1, COLOR_BGR2GRAY); // ת��Ϊ�Ҷ�ͼ��
    cvtColor(distortedImg2, gray2, COLOR_BGR2GRAY);

    vector<Point2f> pts1, pts2;
    vector<uchar> status;
    vector<float> err;

    // �ڵ�һ��ͼ���м��������
    goodFeaturesToTrack(gray1, pts1, 100, 0.01, 10);

    // �������
    calcOpticalFlowPyrLK(gray1, gray2, pts1, pts2, status, err);
    m_pts1 = pts1;
    m_pts2 = pts2;

    // ����������͹����켣
    for (size_t i = 0; i < pts1.size(); ++i) {
        circle(distortedImg1, pts1[i], 5, Scalar(0, 0, 255), -1);
        circle(distortedImg2, pts2[i], 5, Scalar(0, 255, 0), -1);
        line(distortedImg2, pts1[i], pts2[i], Scalar(255, 0, 0), 2);
    }

    // ��ʾ����ͼ��������
    namedWindow("Distorted Image 1", cv::WINDOW_NORMAL);
    imshow("Distorted Image 1", distortedImg1);
    namedWindow("Distorted Image 2", cv::WINDOW_NORMAL);
    imshow("Distorted Image 2", distortedImg2);

    waitKey(0);
    destroyAllWindows();
}

void ExCalibration::RunRt() {
    cv::Mat E = cv::findEssentialMat(m_pts1, m_pts2, camK, RANSAC);
    cv::Mat R1, R2, t;
    cv::decomposeEssentialMat(E, R1, R2, t);
    m_R = R1.clone();
    m_t = -t.clone();
}

void ExCalibration::GetRt(Mat& R, Mat& t) {
    writeParams();
    Getpts();
    RunRt();
    R = m_R;
    t = m_t;
}
#include <iostream>
#include "image.h"
#include"cannyEdgeDetector.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <time.h>
#define REMOVE 10
using namespace std;

int main()
{
	cout << "�����������ͼƬ��ַ(��:\"2.jpg\"��\"D:\\VSData\\DIA\\000026.jpg\"):\n";
	string add;
	cin >> add;
	Image inputImg(add);
//	inputImg.show(add);
	Mat source = inputImg.toMat();
	imshow("InputImage", source);
	Image grayImg=inputImg.toGray();
	Image BW = grayImg.toBW();
	Mat graymat = grayImg.toMat();
//	grayImg.show("GrayImage");
	Mat gray = grayImg.toMat();
	CannyEdgeDetector canny{ 2.0,4,10,30 };
	Image edgeImg=canny.processImage(grayImg);
//	edgeImg.show("Edge");
	Image houghHorImg = edgeImg.houghHor(13*edgeImg.toMat().cols/48);
//	houghHorImg.show("houghHor");
	Image houghVerImg = edgeImg.houghVer(7 * edgeImg.toMat().rows / 32);
//	houghVerImg.show("houghVer");
	Mat region = ((houghVerImg.toMat()&houghHorImg.toMat()));

	int leftup[3] = { 0 };
	leftup[0]=region.rows + region.cols;
	int rightdown[3]= { 0 };
	int leftdown[3] = { 0 };
	leftdown[0]=region.cols;
	int rightup[3] = { 0 };
	rightup[0]=region.rows;
	for (int i = REMOVE; i < region.rows- REMOVE; i++)
	{
		for (int j = REMOVE; j < region.cols- REMOVE; j++)
		{
			if (region.at<uchar>(i, j))
			{
				if ((i + j) < leftup[0])
				{
					leftup[0] = i + j;
					leftup[1] = i;
					leftup[2] = j;
				}
				if ((i + j) > rightdown[0])
				{
					rightdown[0] = i + j;
					rightdown[1] = i;
					rightdown[2] = j;
				}
				if ((j - i) < leftdown[0])
				{
					leftdown[0] = j-i;
					leftdown[1] = i;
					leftdown[2] = j;
				}
				if ((i - j) < rightup[0])
				{
					rightup[0] = i - j;
					rightup[1] = i;
					rightup[2] = j;
				}
			}
		}
	}
	Mat corner = region.clone();
	for (int i = 0; i < region.rows; i++)
	{
		for (int j = 0; j < region.cols; j++)
		{
				corner.at<uchar>(i, j) = 0;
		}
	}
	corner.at<uchar>(leftup[1],leftup[2]) = 255;
	corner.at<uchar>(leftdown[1],leftdown[2]) = 255;
	corner.at<uchar>(rightup[1],rightup[2]) = 255;
	corner.at<uchar>(rightdown[1],rightdown[2]) = 255;
	Mat coradd = grayImg.toMat() | corner;
//	cv::imshow("corneradd", coradd);
//	waitKey(0);
	//p=c1*x+c2*y+c3*x*y+c4
	//q=c5*x+c6*y+c7*x*y+c8
	int rowFinal = grayImg.toMat().rows;
	int colFinal = grayImg.toMat().cols;
	double c1 = 0.0, c2 = 0.0, c3 = 0.0, c4 = 0.0, c5 = 0.0, c6 = 0.0, c7 = 0.0, c8 = 0.0;
	c4 = leftup[1];
	c8 = leftup[2];
	c2 = -(c4 - rightup[1]) / colFinal;
	c6 = -(c8 - rightup[2]) / colFinal;
	c1 =- (c4 - leftdown[1]) / rowFinal;
	c5 = -(c8 - leftdown[2]) / rowFinal;
	c3 = -(c1*rowFinal + c2 * colFinal + c4 - rightdown[1]) / (rowFinal*colFinal);
	c7 = -(c5*rowFinal + c6 * colFinal + c8 - rightdown[2]) / (rowFinal*colFinal);
	Mat recover(rowFinal, colFinal, CV_8UC3);
	for (int i = 0; i < rowFinal; i++)
	{
		for (int j = 0; j < colFinal; j++)
		{
			double p = c1 * i + c2 * j + c3 * i*j + c4;
			double q = c5 * i + c6 * j + c7 * i*j + c8;
			double p2 = p - int(p);
			double p1 = 1 - p2;
			double q1 = q - int(q);
			double q2 = 1 - q1;
			recover.at<Vec3b>(i, j)[0] =int  (source.at<Vec3b>(int(p), int(q))[0] * p1*q2 +
				source.at<Vec3b>(int(p) + 1, int(q))[0] * p2*q2 +
				source.at<Vec3b>(int(p), int(q) + 1)[0] * p1*q1 +
				source.at<Vec3b>(int(p) + 1, int(q) + 1)[0] * p2*q1);
			recover.at<Vec3b>(i, j)[1] = int(source.at<Vec3b>(int(p), int(q))[1] * p1*q2 +
				source.at<Vec3b>(int(p) + 1, int(q))[1] * p2*q2 +
				source.at<Vec3b>(int(p), int(q) + 1)[1] * p1*q1 +
				source.at<Vec3b>(int(p) + 1, int(q) + 1)[1] * p2*q1);
			recover.at<Vec3b>(i, j)[2] = int(source.at<Vec3b>(int(p), int(q))[2] * p1*q2 +
				source.at<Vec3b>(int(p) + 1, int(q))[2] * p2*q2 +
				source.at<Vec3b>(int(p), int(q) + 1)[2] * p1*q1 +
				source.at<Vec3b>(int(p) + 1, int(q) + 1)[2] * p2*q1);
		}
	}
	cv::namedWindow("�ĵ�Ŀ��", WINDOW_AUTOSIZE);
	cv::imshow("�ĵ�Ŀ��", recover);
	waitKey(0);
	return 0;
}
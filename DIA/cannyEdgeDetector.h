#pragma once
#include <opencv2/opencv.hpp>
#include "image.h"

class CannyEdgeDetector
{
private:
	//const float���Ͳ��ܽ������ڳ�ʼ����
	//static const float PI = 3.141592653f;

	//the parameter sigma of gaussian kernel
	float sigma;
	//the radius of the gaussian kernel
	short radius;
	uchar lowThreshold;
	uchar highThreshold;
	//add margin to adapt the mask
	Mat preProcessImage(const Mat& img, int r);
	//remove margin added in the function "preProcessImage"
	//Mat postProcessImage(Mat& img, int r);
	Mat gaussianBlur(Mat& img);
	Mat edgeDetect(Mat& img);
	Mat hysteresis(Mat& img);
	Mat hysteresisRecursion(Mat& img);
public:
	CannyEdgeDetector();
	CannyEdgeDetector(float sig, short r, uchar lowt, uchar hight );
	~CannyEdgeDetector();
	Image processImage(Image& inputImg);
};
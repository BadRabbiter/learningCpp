#pragma once
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

class Image
{
private:
	Mat pic;
	int col;
	int row;
	int channel;
	int Thresh_Otsu(int thresh);
	int choose_Thresh(int thresh_min, int thresh_max);
public:
	Image();
	Image(Mat &img);
	Image(int row, int col, int channel);
	Image(const string &add);
	Image(const char* &add);
	Image toGray();
	Image toBW();
	Image houghHor(int th);
	Image houghVer(int th);
	Mat toMat();
	void show(const string &picName);
	void show(const char* picName);
	void show();
};
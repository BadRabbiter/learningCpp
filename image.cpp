#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include "image.h"
#define RAD_VER  31
#define RAD_HOR 9
using namespace cv;
using namespace std;

Image::Image()
{
	pic = imread("1.jpg");
	row = pic.rows;
	col = pic.cols;
	channel = pic.channels();
}

Image::Image(Mat &img)
{
	pic = img;
	row = pic.rows;
	col = pic.cols;
	channel = pic.channels();
}

Image::Image(int r, int c, int ch)
{
	pic.create(r, c, CV_8UC(ch));
	row = r;
	col = c;
	channel = ch;
}
Image::Image(const string &add)
{
	pic = imread(add);
	row = pic.rows;
	col = pic.cols;
	channel = pic.channels();
}

Image::Image(const char* &add)
{
	pic = imread(add);
	row = pic.rows;
	col = pic.cols;
	channel = pic.channels();
}

Mat Image::toMat()
{
	return pic;
}

void Image::show(const string &picName)
{
	imshow(picName, pic);
	waitKey(0);
}

void Image::show(const char* picName)
{
	imshow(picName, pic);
	waitKey(0);
}

void Image::show()
{
	imshow("Image", pic);
	waitKey(0);
}

Image Image::toGray()
{
	Mat gray(row,col,CV_8UC1);
	if(channel==3)
	{
	for (int i = 0; i < row; i++)
	{
		uchar* dataGray = gray.ptr<uchar>(i);
		for (int j = 0; j < col; j = j + 1)
		{
			dataGray[j] = 0.114*pic.at<Vec3b>(i, j)[0] + 0.587*pic.at<Vec3b>(i, j)[1] + 0.299*pic.at<Vec3b>(i, j)[2];
		}
	}
	Image grayPic{ gray };
	return grayPic;
	}
	else
	{
		cout << "Transition aborted! The input image is not a BGR image!" << endl;
		return pic;
	}
}

int Image::Thresh_Otsu(int thresh)
{
	double gray[256] = { 0 };
	double w0 = 0, u0 = 0, u1 = 0;
	int T;
	for (int i = 0; i < row; i++)
	{
		uchar* data = pic.ptr<uchar>(i);
		for (int j = 0; j < col; j = j + 1)
		{
			gray[data[j]]++;
		}
	}
	for (int i = 0; i <= thresh; i++)
	{
		w0 = w0 + gray[i];
		u0 = u0 + i * gray[i] / (col*row);
	}
	for (int i = thresh + 1; i < 256; i++)
	{
		u1 = u1 + i * gray[i] / (col*row);
	}
	T = w0 * (col*row - w0)*(u0 - u1)*(u0 - u1) / (col*row);
	return T;
}
int Image::choose_Thresh(int thresh_min, int thresh_max)
{
	if (Thresh_Otsu(thresh_max) > Thresh_Otsu(thresh_min))
		thresh_min = (thresh_max + thresh_min) / 2;
	else
		thresh_max = (thresh_max + thresh_min) / 2;
	if (thresh_max == thresh_min || thresh_max - thresh_min == 1)
		return thresh_max;
	else
		choose_Thresh(thresh_min, thresh_max);
}


Image Image::toBW()
{
	int thresh = choose_Thresh(0, 255);
	Mat BW= pic.clone();
	for (int i = 0; i < row; i++)
	{
		uchar* data = BW.ptr<uchar>(i);
		for (int j = 0; j < col; j = j + 1)
		{
			data[j] > thresh ? data[j] = 255 : data[j] = 0;
		}
	}
	Image BWImg{ BW };
	return BWImg;
}

Image Image::houghHor(int th)
{
	float theta[] = { 0,1,2,3,4,
		//170,171,172,173,174,
		//175,176,177,178,179 
		-1,-2,-3,-4
	};
	int maxlam = int(sqrt(row*row + col * col)) + 1;
	float** count = NULL;
	count = new float*[RAD_HOR];
	for (int i = 0; i < RAD_HOR; i++)
	{
		count[i] = new float[maxlam];
	}
	for (int i = 0; i < RAD_HOR; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			count[i][j] = 0;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (pic.at<uchar>(i, j))
			{
				for (int t = 0; t < RAD_HOR; t++)
				{
					int lamda = 0;
					lamda = round(i*cos(theta[t] * CV_PI / 180) + j * sin(theta[t] * CV_PI / 180));
					if ((lamda >= 0) && (lamda < maxlam))
						count[t][lamda]++;
				}
			}	
		}
	}
	int lines = 0;
	for (int i = 0; i < RAD_HOR; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			if (count[i][j] >= th)
			{
				lines++;
			}
		}
	}
	float** para = NULL;
	para = new float*[lines];
	for (int i = 0; i < lines; i++)
	{
		para[i] = new float[2];
	}
	for (int i = 0; i < lines; i++)
	{
		para[i][0] = para[i][1] = 0;
	}
	int co = 0;
	for (int i = 0; i < RAD_HOR; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			if (count[i][j] >= th)
			{
				para[co][0] = theta[i];
				para[co][1] = j;
				co++;
			}
		}
	}
	Mat lineImg = pic.clone();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			lineImg.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			for (int t = 0; t < co; t++)
			{			
					if (para[t][1] == round(i*cos(para[t][0] * CV_PI / 180) + (j*sin(para[t][0] * CV_PI / 180))))
						lineImg.at<uchar>(i, j) = 255;						
			}
		}
	}
	for (int i = 0; i < RAD_HOR; i++)
	{
		delete[] count[i];
	}
	delete[] count;
	for (int i = 0; i < co; i++)
	{
		delete[] para[i];
	}
	delete[] para;
	Image houghImg{ lineImg };
	return houghImg;
}

Image Image::houghVer(int th)
{
	float theta[] = {75,76,77,78,79,80,81,82,83,84,
		85,86,87,88,89,90,91,92,93,94,
		95,96,97,98,99,100,101,102,103,
		104,105 };
	int maxlam = int(sqrt(row*row + col * col))+1;
	float** count = NULL;
	count = new float*[RAD_VER];
	for (int i = 0; i < RAD_VER; i++)
	{
		count[i] = new float[maxlam];
	}
	for (int i = 0; i < RAD_VER; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			count[i][j] = 0;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (pic.at<uchar>(i, j))
			{
				for (int t = 0; t < RAD_VER; t++)
				{
					int lamda = 0;
					lamda = round(i*cos(theta[t] * CV_PI / 180) + j * sin(theta[t] * CV_PI / 180));
					if ((lamda >= 0) && (lamda < maxlam))
						count[t][lamda]++;
				}
			}
		}
	}
	int lines = 0;
	for (int i = 0; i < RAD_VER; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			if (count[i][j] >= th)
			{
				lines++;
			}
		}
	}
	float** para = NULL;
	para = new float*[lines];
	for (int i = 0; i < lines; i++)
	{
		para[i] = new float[2];
	}
	for (int i = 0; i < lines; i++)
	{
		para[i][0] = para[i][1] =  0;
	}
	int co = 0;
	for (int i = 0; i < RAD_VER; i++)
	{
		for (int j = 0; j < maxlam; j++)
		{
			if (count[i][j] >= th)
			{
				para[co][0] = theta[i];
				para[co][1] = j;
				co++;
			}
		}
	}
	Mat lineImg = pic.clone();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			lineImg.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			for (int t = 0; t < co; t++)
			{
					if (para[t][1] == round(i*cos(para[t][0] * CV_PI / 180) + (j*sin(para[t][0] * CV_PI / 180))))
							lineImg.at<uchar>(i, j) = 255;		
			}
		}
	}
	for (int i = 0; i < RAD_VER; i++)
	{
		delete[] count[i];
	}
	delete[] count;
	for (int i = 0; i < co; i++)
	{
		delete[] para[i];
	}
	delete[] para;
	Image houghImg{ lineImg };
	return houghImg;
}
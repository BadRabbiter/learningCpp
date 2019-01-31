#include <cmath>
#include <opencv2/opencv.hpp>
#include "cannyEdgeDetector.h"
#include "image.h"

CannyEdgeDetector::CannyEdgeDetector()
{
	sigma = 1.0;
	radius = 1;
	lowThreshold=30;
	highThreshold=80;
}

CannyEdgeDetector::CannyEdgeDetector(float sig=1.0, short r=1, uchar lowt=30, uchar hight=80)
{
	sigma = sig;
	radius = r;
	lowThreshold = lowt;
	highThreshold = hight;
}

CannyEdgeDetector::~CannyEdgeDetector(){;}

Mat CannyEdgeDetector::preProcessImage(const Mat& img, int r)
{
	Mat proImg(img.rows + 2 * r, img.cols + 2 * r, CV_8UC1);
	//����ԭͼ
	for (int i = r; i < proImg.rows - r; i++)
	{
		for (int j = r; j < proImg.cols - r; j++)
		{
			proImg.at<uchar>(i, j) = img.at<uchar>(i - r, j - r);
		}
	}
	//�����ϲ��հ�
	for (int i = 0; i < r; i++)
	{
		for (int j = r; j < proImg.cols - r; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2*r-i, j);
		}
	}
	//�����²��հ�
	for (int i = proImg.rows - r; i < proImg.rows; i++)
	{
		for (int j = r; j < proImg.cols - r; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2 * (proImg.rows - r-1) - i, j);
		}
	}
	//�������հ�
	for (int i = r; i < proImg.rows - r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(i , 2*r-j);
		}
	}
	//�����Ҳ�հ�
	for (int i = r; i < proImg.rows - r; i++)
	{
		for (int j = proImg.cols-r; j < proImg.cols; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(i, 2 * (proImg.cols-r-1)-j);
		}
	}
	//�������Ͻ�
	for (int i = 0; i <  r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2*r-i, 2*r-j);
		}
	}
	//�������Ͻ�
	for (int i = 0; i < r; i++)
	{
		for (int j = proImg.cols-r; j < proImg.cols; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2 * r - i, 2 * (proImg.cols-r-1)-j);
		}
	}
	//�������½�
	for (int i = proImg.rows - r; i < proImg.rows; i++)
	{
		for (int j = 0; j < r; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2 * (proImg.rows - r - 1) - i, 2 * r - j);
		}
	}
	//�������½�
	for (int i = proImg.rows-r; i < proImg.rows; i++)
	{
		for (int j = proImg.cols - r; j < proImg.cols; j++)
		{
			proImg.at<uchar>(i, j) = proImg.at<uchar>(2 * (proImg.rows-r-1)- i, 2 * (proImg.cols - r - 1) - j);
		}
	}
	return proImg;
}

Mat CannyEdgeDetector::gaussianBlur(Mat& img)
{
	Mat gaussImg = img.clone();
	Mat proImg = preProcessImage(img, radius);
	float** kernel = NULL;
	double total = 0;
	int masksize = 2 * radius + 1;
	kernel = new float*[masksize];
	for (int i = 0; i < masksize; i++)
	{
		kernel[i] = new float[masksize];
	}
	for (int i = 0; i < masksize; i++)
	{
		for (int j = 0; j < masksize; j++)
		{
			kernel[i][j] = exp(-((i - radius)*(i - radius) + (j - radius)*(j - radius)) / (2 * sigma*sigma)) / (2 * CV_PI*sigma*sigma);
			total += kernel[i][j];
		}
	}
	for (int i = radius; i < proImg.rows - radius; i++)
	{
		for (int j = radius; j < proImg.cols - radius; j++)
		{
			float value = 0.0;
			for (int s = 0; s < masksize; s++)
			{
				for (int t = 0; t < masksize; t++)
				{
					value += kernel[s][t] * proImg.at<uchar>(i + s - radius, j + t - radius);
				}
			}
			gaussImg.at<uchar>(i-radius, j-radius) = round(value);
		}
	}
	for (int i = 0; i < 2 * radius + 1; i++)
	{
		delete[] kernel[i];
	}
	delete[] kernel;
	return gaussImg;
}
Mat CannyEdgeDetector::edgeDetect(Mat& img)
{
	Mat magImg = img.clone();
	Mat proImg = preProcessImage(img, 1);
	float** mag = NULL;
	float** ang = NULL;
	double gx = 0.0, gy = 0.0, max = 0.0, angle=0.0;
	mag = new float*[img.rows];
	ang = new float*[img.rows];
	for (int i = 0; i < img.rows; i++)
	{
		mag[i] = new float[img.cols];
	    ang[i] = new float[img.cols];
	}
	for (int i = 1; i < proImg.rows - 1; i++)
	{
		for (int j = 1; j < proImg.cols - 1; j++)
		{
			gx = float(2 * proImg.at<uchar>(i, j + 1) - 2 * proImg.at<uchar>(i, j - 1) +
				proImg.at<uchar>(i - 1, j + 1) - proImg.at<uchar>(i - 1, j - 1) +
				proImg.at<uchar>(i + 1, j + 1) - proImg.at<uchar>(i + 1, j - 1));
			gy = float(2 * proImg.at<uchar>(i-1, j) - 2 * proImg.at<uchar>(i+1, j) +
				proImg.at<uchar>(i - 1, j - 1) - proImg.at<uchar>(i + 1, j - 1) +
				proImg.at<uchar>(i - 1, j + 1) - proImg.at<uchar>(i + 1, j +1));
			mag[i - 1][j - 1] = sqrt(gx*gx + gy * gy);
			max = mag[i - 1][j - 1] > max ? mag[i - 1][j - 1] : max;
			angle = atan2(gy, gx) * 180 / CV_PI;
			if (((angle > -22.5) && (angle <= 22.5)) ||
				((angle > 157.5) || (angle <= -157.5)))
			{
				ang[i - 1][j - 1] = 0;
			}
			else if (((angle > 22.5) && (angle <= 67.5)) ||
				((angle > -157.5) && (angle <= -112.5)))
			{
				ang[i - 1][j - 1] = 45;
			}
			else if (((angle > 67.5) && (angle <= 112.5)) ||
				((angle > -112.5) && (angle <= -67.5)))
			{
				ang[i - 1][j - 1] = 90;
			}
			else if (((angle > 112.5) && (angle <= 157.5)) ||
				((angle > -67.5) && (angle <= -22.5)))
			{
				ang[i - 1][j - 1] = 135;
			}
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			magImg.at<uchar>(i, j) = 255 * mag[i][j] / max;
		}
	}
	// nonMaxSuppression

	Mat maxImg = magImg.clone();
	for (int i = 1; i < img.rows-1; i++)
	{
		for (int j = 1; j < img.cols-1; j++)
		{
			if (ang[i][j] == 0)
			{
				if (!(magImg.at<uchar>(i, j) > magImg.at<uchar>(i, j - 1) &&
					magImg.at<uchar>(i, j) > magImg.at<uchar>(i, j + 1)))
					maxImg.at<uchar>(i, j) = 0;
			}
			else if (ang[i][j] == 45)
			{
				if (!(magImg.at<uchar>(i, j) > magImg.at<uchar>(i-1, j + 1) &&
					magImg.at<uchar>(i, j) > magImg.at<uchar>(i+1, j - 1)))
					maxImg.at<uchar>(i, j) = 0;
			}
			else if (ang[i][j] == 90)
			{
				if (!(magImg.at<uchar>(i, j) > magImg.at<uchar>(i-1, j) &&
					magImg.at<uchar>(i, j) > magImg.at<uchar>(i+1, j)))
					maxImg.at<uchar>(i, j) = 0;
			}
			else  if (ang[i][j] == 135)
			{
				if (!(magImg.at<uchar>(i, j) > magImg.at<uchar>(i-1, j - 1) &&
					magImg.at<uchar>(i, j) > magImg.at<uchar>(i+1, j + 1)))
					maxImg.at<uchar>(i, j) = 0;
			}
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		delete[] mag[i];
		delete[] ang[i];
	}
	delete[] mag;
	delete[] ang;
	return maxImg;
}

Mat CannyEdgeDetector::hysteresis(Mat& img)
{
	Mat cannyImg = img.clone();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) >= highThreshold)
			{
				cannyImg.at<uchar>(i, j) = 255;
			}
		}
	}
	cannyImg = hysteresisRecursion(cannyImg);
	for (int i = 0; i < cannyImg.rows; i++)
	{
		for (int j = 0; j < cannyImg.cols; j++)
		{
			if (cannyImg.at<uchar>(i, j) != 255)
				cannyImg.at<uchar>(i, j) = 0;
		}
	}
	return cannyImg;
}
Mat CannyEdgeDetector::hysteresisRecursion(Mat& img)
{
	Mat cannyImg = img.clone();
	long elemChange = 0;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) == 255)
			{
				for (int p = i - 1; p < i + 2; p++)
				{
					for (int q = j - 1; q < j + 2; q++)
					{
						if ((p >= 0) && (q >= 0) && (p < img.rows) && (q < img.cols) && (p != i) && (q != j))
						{
							if ((img.at<uchar>(p, q) != 255)&& (img.at<uchar>(p, q) > lowThreshold))
							{
									cannyImg.at<uchar>(p, q) = 255;
									elemChange++;
							}
						}
					}
				}
			}
		}
	}
	if (elemChange)
		return hysteresisRecursion(cannyImg);
	else
		return cannyImg;
}

Image CannyEdgeDetector:: processImage(Image& inputImg)
{
	Mat img = inputImg.toMat();
	Mat gaussImg = gaussianBlur(img);
	Mat edgeImg = edgeDetect(gaussImg);
	Mat cannyImg = hysteresis(edgeImg);
	Image cannyResult{ cannyImg };
	return cannyResult;
}
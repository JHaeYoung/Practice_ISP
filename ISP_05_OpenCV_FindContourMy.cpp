#pragma once

#include "../Common/Common.h"
#include "ISP.h"


int main() {


	ISP _isp;


	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "rectangle.png";
	Mat color_img = Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));

	uchar* pData = color_img.data;
	size_t width = color_img.cols;
	size_t height = color_img.rows;
	size_t length = width * height;

	const int histoSZ = 256;
	//#1 Convert Color to Gray
	Mat gray_img = Mat::zeros(height, width, CV_8UC1);
	uchar* pDataGray = gray_img.data;
	_isp.Convert_BGRtoGray(pData, width, height, pDataGray);

	for (size_t i = 0; i < length; i++)
	{
		pDataGray[i] < 230 ? pDataGray[i] = 255 : pDataGray[i] = 0;
	}
	//À±°û¼± Ã£±â
	std::vector<std::vector<cv::Point>> contours;
	std::vector< cv::Vec4i> hierarchy;
	cv::findContours(gray_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//À±°û¼± ±×¸®±â
	RNG rng(12345);
	cv::Mat contourImage = cv::Mat::zeros(gray_img.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(contourImage, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

	}


	cv::Rect rt = cv::boundingRect(contours[0]);

	cv::rectangle(color_img, rt, Scalar(0, 0, 255), 1);



	return 0;

}
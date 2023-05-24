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

	_isp.Get_length(pDataGray, width, height);

	return 1;
}


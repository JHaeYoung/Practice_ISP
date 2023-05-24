#pragma once

#include "../Common/Common.h"
#include "ISP.h"


int main() {


	ISP _isp;


	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "lena.jpg";
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

	//#2 new Alloc Buffer LPF_Image
	Mat lpf_img = Mat::zeros(height, width, CV_8UC1);
	uchar* pDataLPF = lpf_img.data;
	_isp.Get_LPF(pDataGray, width, height, pDataLPF);

	// 3. High Pass Filter
	Mat hpf_img1 = Mat::zeros(height, width, CV_8UC1);
	uchar* pDataHPF1 = hpf_img1.data;
	_isp.Get_HPF1(pDataGray, width, height, pDataHPF1);

	//#4 라플라시안
	Mat hpf_img2 = Mat::zeros(height, width, CV_8UC1);
	uchar* pDataHPF2 = hpf_img2.data;
	_isp.Get_HPF2(pDataGray, width, height, pDataHPF2);

	{
		//float lpf_kenel[9] = {
		//	1.0 / 9, 1.0 / 9, 1.0 / 9,
		//	1.0 / 9, 1.0 / 9, 1.0 / 9,
		//	1.0 / 9, 1.0 / 9, 1.0 / 9 };

		//for (size_t row = 1; row < height - 1; row++)
		//{
		//	for (size_t col = 1; col < width - 1; col++)
		//	{
		//		int temp = lpf_kenel[0] * pDataGray[(row - 1) * width + (col - 1)];//(-1,-1)
		//		temp += lpf_kenel[1] * pDataGray[(row - 1) * width + (col - 0)];//(-1,0)
		//		temp += lpf_kenel[2] * pDataGray[(row - 1) * width + (col + 1)];//(-1,1)
		//		temp += lpf_kenel[3] * pDataGray[(row - 0) * width + (col - 1)];//(0,-1)
		//		temp += lpf_kenel[4] * pDataGray[(row - 0) * width + (col - 0)];//(0,0)
		//		temp += lpf_kenel[5] * pDataGray[(row - 0) * width + (col + 1)];//(0,1)
		//		temp += lpf_kenel[6] * pDataGray[(row + 1) * width + (col - 1)];//(+1,-1)
		//		temp += lpf_kenel[7] * pDataGray[(row + 1) * width + (col - 0)];//(+1,0)
		//		temp += lpf_kenel[8] * pDataGray[(row + 1) * width + (col + 1)];//(+1,1)

		//		pDataLPF[(row)*width + (col)] = temp;
		//		lpf_img.data[(row)*width + (col)] = temp;
		//	}
		//}
		//int last_col = width * height - width;
		//int last_row = width * height - width;


		//for (size_t col = 1; col < width; col++)
		//{
		//	lpf_img.data[col] = lpf_img.data[width + col];
		//	lpf_img.data[last_col + col] = lpf_img.data[last_col - width + col];
		//}
		//for (size_t row = 1; row < height; row++)
		//{
		//	lpf_img.data[row * width] = lpf_img.data[row * width + 1];
		//	lpf_img.data[(row)*width - 1] = lpf_img.data[(row)*width - 2];
		//}

		//lpf_img.data[0] = lpf_img.data[1];
		//lpf_img.data[length - 1] = lpf_img.data[length - 2];
	}
	//상황....Low Pass Filter 이미지를 전송하다 아래 위치에서 이미지 손실이 발생했습니다.
	//아래 위치에서 손실된 부분을 찾아서 이미지를 개선하세요

	int row, col;
	row = 10, col = 10;

	int x, x1, x0, y, y1, y0;
	x = 10;
	x1 = col + 1;
	x0 = col - 1;
	y = lpf_img.data[(row)*width + (x)];
	y1 =lpf_img.data[(row)*width + (x1)];
	y0 = lpf_img.data[(row)*width + (x0)];


	y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);

	
	row = 100; col = 100;
	lpf_img.data[(row)*width + (col)] = 0;



	return 0;

}
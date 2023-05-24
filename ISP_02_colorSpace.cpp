#pragma once

#include "../Common/Common.h"

void Spilt_ColorToRGB(uchar* pDataRGB, size_t& w, size_t& h, uchar* pR, uchar* pG, uchar* pB/*, Mat* pColor_img*/) {

	for (size_t row = 0; row < h; row++)
	{
		for (size_t col = 0; col < w; col++)
		{
			int index = row * w + col;
			//if (pColor_img->channels() == 3) //color
			{
				index *= 3;
			}
			//else if (pColor_img->channels() == 1) // gray
			//{
			//}
			int b = pDataRGB[index + 0];
			int g = pDataRGB[index + 1];
			int r = pDataRGB[index + 2];

			int band_index = row * w + col;
			pR[band_index] = r;
			pG[band_index] = g;
			pB[band_index] = b;
		}
	}


}

void Convert_BGRtoYCbCr(uchar* pDataBGR, size_t& w, size_t& h, uchar* pY, uchar* pCb, uchar* pCr, Mat* pColor_img) {

	for (size_t row = 0; row < h; row++)
	{
		for (size_t col = 0; col < w; col++)
		{	
			int index = row * w + col;
			if (pColor_img->channels() == 3) //color
			{
				index *= 3;
			}
			else if (pColor_img->channels() == 1) // gray
			{
			}
			int b = pDataBGR[index + 0];
			int g = pDataBGR[index + 1];
			int r = pDataBGR[index + 2];

			int y = 0.299*r + 0.587*g + 0.114*b;
			int Cb = (-(0.169) * r)+(-(0.331)*g) + 0.500*b;
			int Cr = 0.500*r+(-(0.419)*g)+(-(0.0813)*b);
			
			int band_index = row * w + col;
			pY[band_index] = y;
			pCb[band_index] = Cb;
			pCr[band_index] = Cr;
		}

	}

}


int main() {

	cout << "hello OpenCV world!!" << endl;

	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "baboon.jpg";

	Mat* pColor_img;
	pColor_img = new Mat(cv::imread(filename, cv::ImreadModes::IMREAD_COLOR));
	//Mat color_img = cv::imread(filename, cv::ImreadModes::IMREAD_COLOR);

	uchar* pData = pColor_img->data;
	size_t width = pColor_img->cols;
	size_t height = pColor_img->rows;

	Mat img_R = Mat(height, width, CV_8UC1); //openCV 8 bit
	Mat img_G = Mat(height, width, CV_8UC1); //openCV 8 bit
	Mat img_B = Mat(height, width, CV_8UC1); //openCV 8 bit
	uchar* pData_R = img_R.data;
	uchar* pData_G = img_G.data;
	uchar* pData_B = img_B.data;

	Mat img_Y= Mat(height, width, CV_8UC1);
	Mat img_Cb = Mat(height, width, CV_8UC1);
	Mat img_Cr = Mat(height, width, CV_8UC1);
	uchar* pData_Y = img_Y.data;
	uchar* pData_Cb = img_Cb.data;
	uchar* pData_Cr = img_Cr.data;

	Spilt_ColorToRGB(pData, width, height, pData_R, pData_G, pData_B, pColor_img);
	Convert_BGRtoYCbCr(pData, width, height, pData_Y, pData_Cb, pData_Cr, pColor_img);
	
}

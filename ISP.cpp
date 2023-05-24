#pragma once

#include "ISP.h"

ISP::ISP()
{
	cout << "ISP::ctor" << endl;

}
ISP::~ISP()
{
	cout << "ISP::dtor" << endl;

}



void ISP::Convert_BGRtoGray(uchar* pDataBRG, size_t& w, size_t& h, uchar* pY)
{
	for (size_t row = 0; row < h; row++)
	{
		for (size_t col = 0; col < w; col++)
		{
			int index = row * w + col;
			index *= 3;
			int b = pDataBRG[index + 0];
			int g = pDataBRG[index + 1];
			int r = pDataBRG[index + 2];

			int bandindex = row * w + col;
			pY[bandindex] = 0.299 * r + 0.587 * g + 0.114 * b;

		}
	}
}



void ISP::Get_Histogram(uchar* pDataGray, size_t length, int* pHisto) {

	for (size_t i = 0; i < length; i++)
	{
		pHisto[pDataGray[i]]++;
	} //이렇게 해도 위와 똑같음 
}

void ISP::Get_LPF(uchar* pDataGray, size_t& width, size_t& height, uchar* pDataLPF)
{
	int length = width * height;
	float sobel_x[9] = {
	1.0 / 9, 1.0 / 9, 1.0 / 9,
	1.0 / 9, 1.0 / 9, 1.0 / 9,
	1.0 / 9, 1.0 / 9, 1.0 / 9 };

	for (size_t row = 1; row < height - 1; row++)
	{
		for (size_t col = 1; col < width - 1; col++)
		{
			int temp = sobel_x[0] * pDataGray[(row - 1) * width + (col - 1)];//(-1,-1)
			temp += sobel_x[1] * pDataGray[(row - 1) * width + (col - 0)];//(-1,0)
			temp += sobel_x[2] * pDataGray[(row - 1) * width + (col + 1)];//(-1,1)
			temp += sobel_x[3] * pDataGray[(row - 0) * width + (col - 1)];//(0,-1)
			temp += sobel_x[4] * pDataGray[(row - 0) * width + (col - 0)];//(0,0)
			temp += sobel_x[5] * pDataGray[(row - 0) * width + (col + 1)];//(0,1)
			temp += sobel_x[6] * pDataGray[(row + 1) * width + (col - 1)];//(+1,-1)
			temp += sobel_x[7] * pDataGray[(row + 1) * width + (col - 0)];//(+1,0)
			temp += sobel_x[8] * pDataGray[(row + 1) * width + (col + 1)];//(+1,1)

			pDataLPF[(row)*width + (col)] = temp;
			//lpf_img.data[(row)*width + (col)] = temp;
		}
	}
	int last_col = width * height - width;
	int last_row = width * height - width;


	for (size_t col = 1; col < width; col++)
	{
		pDataLPF[col] = pDataLPF[width + col];
		pDataLPF[last_col + col] = pDataLPF[last_col - width + col];
	}
	for (size_t row = 1; row < height; row++)
	{
		pDataLPF[row * width] = pDataLPF[row * width + 1];
		pDataLPF[(row)*width - 1] = pDataLPF[(row)*width - 2];
	}

	pDataLPF[0] = pDataLPF[1];
	pDataLPF[length - 1] = pDataLPF[length - 2];
}

void ISP::Get_HPF1(uchar* pDataGray, size_t& width, size_t& height, uchar* pDataHPF)
{
	int length = width * height;
	float sobel_x[9] = {
	-1,-2,-1,
	0,0,0,
	1,2,1};

	float sobel_y[9] = {
	1,0,-1,
	2,0,-2,
	1,0,-1 };
	bool dir = false; //false -x, true - y

	if (dir == false) {
		for (size_t row = 1; row < height - 1; row++)
		{
			for (size_t col = 1; col < width - 1; col++)
			{
				int gX = sobel_x[0] * pDataGray[(row - 1) * width + (col - 1)];//(-1,-1)
				gX += sobel_x[1] * pDataGray[(row - 1) * width + (col - 0)];//(-1,0)
				gX += sobel_x[2] * pDataGray[(row - 1) * width + (col + 1)];//(-1,1)
				gX += sobel_x[3] * pDataGray[(row - 0) * width + (col - 1)];//(0,-1)
				gX += sobel_x[4] * pDataGray[(row - 0) * width + (col - 0)];//(0,0)
				gX += sobel_x[5] * pDataGray[(row - 0) * width + (col + 1)];//(0,1)
				gX += sobel_x[6] * pDataGray[(row + 1) * width + (col - 1)];//(+1,-1)
				gX += sobel_x[7] * pDataGray[(row + 1) * width + (col - 0)];//(+1,0)
				gX += sobel_x[8] * pDataGray[(row + 1) * width + (col + 1)];//(+1,1)

				//lpf_img.data[(row)*width + (col)] = temp;
	//		}
	//	}
	//}else
	//	for (size_t row = 1; row < height - 1; row++)
	//	{
	//		for (size_t col = 1; col < width - 1; col++)
	//		{
				int gY = sobel_y[0] * pDataGray[(row - 1) * width + (col - 1)];//(-1,-1)
				gY += sobel_y[1] * pDataGray[(row - 1) * width + (col - 0)];//(-1,0)
				gY += sobel_y[2] * pDataGray[(row - 1) * width + (col + 1)];//(-1,1)
				gY += sobel_y[3] * pDataGray[(row - 0) * width + (col - 1)];//(0,-1)
				gY += sobel_y[4] * pDataGray[(row - 0) * width + (col - 0)];//(0,0)
				gY += sobel_y[5] * pDataGray[(row - 0) * width + (col + 1)];//(0,1)
				gY += sobel_y[6] * pDataGray[(row + 1) * width + (col - 1)];//(+1,-1)
				gY += sobel_y[7] * pDataGray[(row + 1) * width + (col - 0)];//(+1,0)
				gY += sobel_y[8] * pDataGray[(row + 1) * width + (col + 1)];//(+1,1)

				pDataHPF[(row)*width + (col)] = abs(gY) +abs(gX);
				//lpf_img.data[(row)*width + (col)] = temp;
			}
		}
	}

	int last_col = width * height - width;
	int last_row = width * height - width;


	for (size_t col = 1; col < width; col++)
	{
		pDataHPF[col] = pDataHPF[width + col];
		pDataHPF[last_col + col] = pDataHPF[last_col - width + col];
	}
	for (size_t row = 1; row < height; row++)
	{
		pDataHPF[row * width] = pDataHPF[row * width + 1];
		pDataHPF[(row)*width - 1] = pDataHPF[(row)*width - 2];
	}

	pDataHPF[0] = pDataHPF[1];
	pDataHPF[length - 1] = pDataHPF[length - 2];
}

void ISP::Get_HPF2(uchar* pDataGray, size_t& width, size_t& height, uchar* pDataHPF)
{
	int length = width * height;
	float kernel[9] = {
	0,1,0,
	1,-4,1,
	0,1,0 };

	bool dir = false; //false -x, true - y

	if (dir == false) {
		for (size_t row = 1; row < height - 1; row++)
		{
			for (size_t col = 1; col < width - 1; col++)
			{
				int temp = kernel[0] * pDataGray[(row - 1) * width + (col - 1)];//(-1,-1)
				temp += kernel[1] * pDataGray[(row - 1) * width + (col - 0)];//(-1,0)
				temp += kernel[2] * pDataGray[(row - 1) * width + (col + 1)];//(-1,1)
				temp += kernel[3] * pDataGray[(row - 0) * width + (col - 1)];//(0,-1)
				temp += kernel[4] * pDataGray[(row - 0) * width + (col - 0)];//(0,0)
				temp += kernel[5] * pDataGray[(row - 0) * width + (col + 1)];//(0,1)
				temp += kernel[6] * pDataGray[(row + 1) * width + (col - 1)];//(+1,-1)
				temp += kernel[7] * pDataGray[(row + 1) * width + (col - 0)];//(+1,0)
				temp += kernel[8] * pDataGray[(row + 1) * width + (col + 1)];//(+1,1)

				pDataHPF[(row)*width + (col)] = abs(temp);

			}
		}
	}

	int last_col = width * height - width;
	int last_row = width * height - width;


	for (size_t col = 1; col < width; col++)
	{
		pDataHPF[col] = pDataHPF[width + col];
		pDataHPF[last_col + col] = pDataHPF[last_col - width + col];
	}
	for (size_t row = 1; row < height; row++)
	{
		pDataHPF[row * width] = pDataHPF[row * width + 1];
		pDataHPF[(row)*width - 1] = pDataHPF[(row)*width - 2];
	}

	pDataHPF[0] = pDataHPF[1];
	pDataHPF[length - 1] = pDataHPF[length - 2];
}

void ISP::Get_length(uchar* pDataGray, size_t& width, size_t& height)
{
	int length = width * height;
	int x0=0,x1=0,y0=0,y1=0;
	for (int row = length /2; row < length / 2+width; row++)
	{
		if (pDataGray[row] != 255) {
			x0 = row;
			break;
		}
		
	}
	for (int row = x0 ; row < length / 2 + width; row++)
	{
		if (pDataGray[row] == 255) {
			x1 = row;
			break;
		}

	}	
	for (size_t row = 0; row < height; row++)
	{
		if (pDataGray[row * width + width / 2] != 255)
		{
			y0 = row;
			break;
		}
		
	}
	for (size_t row = y0; row < height; row++)
	{
		if (pDataGray[row * width + width / 2] == 255)
		{
			y1 = row;
			break;
		}

	}
	
	int x = x1 - x0;
	int y = y1 - y0;

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

}


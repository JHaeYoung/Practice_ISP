#pragma once

#include "../Common/Common.h"

void Convert_BGRtoGray(uchar* pDataBRG, size_t& w, size_t& h, uchar* pY)
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

void Get_Histogram(uchar* pDataGray, size_t length, int* pHisto) {
	
	for(size_t i=0; i< length; i++)
	{
		pHisto[pDataGray[i]]++;
	} //이렇게 해도 위와 똑같음 
}

void CDistribution(int* pHisto, int Histo_length, int* CDData) {

	for (size_t i = 1; i < Histo_length; i++)
	{
		CDData[i] = pHisto[i] + CDData[i - 1];
		/*cout << i << "번 히스토 : " << pHisto[i] << endl;
		cout <<i <<"번 분포 : " << CDData[i] << endl;*/
	}


}

int main() {


	cout << "hello OpenCV world!!" << endl;


	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "lena.jpg";
	Mat color_img = Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));

	uchar* pData = color_img.data;
	size_t width = color_img.cols;
	size_t height = color_img.rows;

	const int histoSZ = 256;
	//#1 Convert Color to Gray
	Mat gray_img = Mat::zeros(height, width, CV_8UC1);
	Mat gray_img_histoEq = Mat::zeros(height, width, CV_8UC1);

	//Mat* mat = new Mat();
	//mat = new Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));

	uchar* pDataGray = gray_img.data;
	Convert_BGRtoGray(pData, width, height, pDataGray);

	//#2 Get Histogram
	int histo[histoSZ] = { 0, };
	size_t length = width * height;
	Get_Histogram(pDataGray, length, histo);

	//#확률 밀도 함수
	size_t Histo_length = sizeof(histo) / sizeof(*histo);
	int CDData[histoSZ] = { 0, };
	CDistribution(histo, Histo_length, CDData);
	CDData[0] = histo[0];
	for (size_t i = 1; i < Histo_length; i++)
	{
		CDData[i] = histo[i] + CDData[i - 1];
		cout << i << "번 히스토 : " << histo[i] << endl;
		cout << i << "번 분포 : " << CDData[i] << endl;
	}

	//#4 영상의 각 화소 값들로부터 대응화소 값으로 매핑
	int new_gray[histoSZ] = { 0, };
	size_t N = length; //밝기 최대 값, 전체 크기

	for (size_t i = 0; i < histoSZ; i++)
	{
		new_gray[i] = 1.0 * (CDData[i] * 255) / N;

	}
	for (size_t i = 0; i < N; i++)
	{
		gray_img_histoEq.data[i] = new_gray[gray_img.data[i]];
	}

	//std::ofstream oFile("histogram_eq.csv");

	//std::string	str = "gray, histo, histo_eq";
	//if (oFile.is.open())
	//{
	// 
	//
	//std::format("{}, {}, {}\n", i, histo[i], new_gray);
	
	//Python과 비슷한 기능인 format 헤더파일을 추가해 사용할 수 있다.

	{
		Mat gray_img;
		cvtColor(color_img, gray_img, COLOR_BGR2GRAY);
		cv::equalizeHist(gray_img, gray_img_histoEq);
		int a = 0;

		Mat diff = gray_img_histoEq - gray_img;
		Scalar sum = cv::sum(diff);
	}

	return 0;

}
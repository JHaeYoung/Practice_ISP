#pragma once

#include "../Common/Common.h"

int* Histo_Norm(int* pHisto, size_t& length, int& a, int& b) {
	const int sz = 256;
	int* nor_histo = new int[256];
	int min = pHisto[0];
	int max = pHisto[0];

	for (int i = 0; i < length; i++) {
		if (max < pHisto[i])max = pHisto[i];
		if (min > pHisto[i])min = pHisto[i];

	}
	////동적 포인터
	//auto minmax = std::minmax_element(pHisto, pHisto + length);
	////정적
	////auto minmax = std::minmax_element(std::begin(pHisto), std::end(pHisto));
	//min = *minmax.first;
	//max = *minmax.second;

	//int histo[sz] = { 0, };
	//memcpy(histo,const_cast<int*>(pHisto), sizeof(int) * sz);
	//std::sort(histo, histo + length);
	//min = histo[0];
	//max = histo[sz-1];


	for (int i = 0; i < length; i++) {
		nor_histo[i] = a + (1.0*(pHisto[i] - min) * (b - a) / (max - min));
	}
	return nor_histo;
}

void histoDisplay(uchar* pData, size_t& width, size_t& height) {
	int index = 0;
	int data[256] = { 0, };
	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			index = row * width + col;

			data[pData[index]]++;
		}
	}

	//for(size_t i=0; i<width * height; i++)
	//{	data[pData[i]]++;
	//} //이렇게 해도 위와 똑같음 

	size_t Histo_length = sizeof(data)/sizeof(*data);
	int a = 0;
	int b = 190;

	int* pHisto=Histo_Norm(data, Histo_length, a, b);


	for (size_t i = 0; i < 256; i++)
	{
		cout << " [" << i << "] | ";
		for (int j = 0; j < pHisto[i]; j++) {
			cout << "*";
		}
		cout << " " << (int)data[i] << endl;
		
	}
	cout << typeid(pHisto).name()<< endl;
	delete[] pHisto;
}


int main() {

	cout << "hello OpenCV world!!" << endl;

	string fileName = "jetson.bmp";
	Mat img = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);
	Mat gray_image = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	Mat color_image = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);

	/*밝기 분포 계산 */
	uchar* pData1 = color_image.data;
	uchar* pData = gray_image.data;
	size_t width = color_image.cols;
	size_t height = color_image.rows;
	
	//code - histgram을 구하고 출력하시오	
	histoDisplay(pData, width, height);
	histoDisplay(pData1, width, height);

	//이미지 출력 윈도우 설정
	const char* window_name = "OpenCV Window";
	cv::namedWindow(window_name, cv::WindowFlags::WINDOW_NORMAL);
	cv::resizeWindow(window_name, 640, 480); //윈도우 크기 변경
	
	//이미지 출력
	cv::imshow(window_name, gray_image);
	cv::waitKey();

	//이미지 출력 윈도우 해제
	cv::destroyWindow(window_name);



	

	return 1;



}
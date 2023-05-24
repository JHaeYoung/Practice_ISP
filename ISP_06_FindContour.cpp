#pragma once

#include "../Common/Common.h"
#include "ISP.h"


int main() {


	ISP _isp;


	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "opencv-logo.png";
	Mat src_color = Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));
	//Color RGB -> Convert RGB to HSV
	Mat src_HSV;
	cvtColor(src_color, src_HSV, COLOR_BGR2HSV);

	//Detect Shape
	int low_H = 150;
	int high_H = 180;
	int low_S = 0;
	int high_S = 255;
	int low_V = 0;
	int high_V = 255;

	Scalar lower_R(low_H, low_S, low_V);
	Scalar high_R(high_H, high_S, high_V);
	Mat detect_img_R;
	inRange(src_HSV, lower_R, high_R, detect_img_R);

	low_H = 45;
	high_H = 100;
	Mat detect_img_G;
	Scalar lower_G(low_H, low_S, low_V);
	Scalar high_G(high_H, high_S, high_V);
	inRange(src_HSV, lower_G, high_G, detect_img_G);

	low_H = 60;
	high_H = 120;
	Mat detect_img_B;
	Scalar lower_B(low_H, low_S, low_V);
	Scalar high_B(high_H, high_S, high_V);
	inRange(src_HSV, lower_B, high_B, detect_img_B);

	if(false){
		Mat reduced_R = src_color.clone();
		cvtColor(detect_img_R, detect_img_R, CV_GRAY2BGR);
		bitwise_and(reduced_R, detect_img_R, reduced_R);
	}
	
	{//reduced_R = reduced_R


	/*Mat imgA, imgB, imgAnd;
	bitwise_and();*/

	//Get Parameters HSV for OpenCV -logo.png
	//Grean : H 45, 100
	//Blue : H 60, 120
	//Red : H 150, 180

	//Threhold -> binary, ÀÌÁøÈ­
	//input[0,1,2,3,4,5]
	/*
		threshhold -3
		if input >3  output =10...255
		else   output 0...0
			output[0,1,2,3,4,5]
	inrange(src, dst, min,max) -> min~ max -> 255 else 0*/

	}

	//Calc feature

		//À±°û¼± Ã£±â
	RNG rng(12345);
	vector<vector<cv::Point>> contours;
	std::vector< cv::Vec4i> hierarchy;
	cv::findContours(detect_img_R, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	int max_index = 0;
	double max_length = 0;
	//À±°û¼± ±×¸®±â
	for (size_t i = 0; i < contours.size(); i++)
	{
		double length = cv::arcLength(contours[i], false);
		double area = cv::contourArea(contours[i]);
		RotatedRect rt  = cv::minAreaRect(contours[i]);

		if (contours[i].size() < 5) continue;
		
		RotatedRect ellipse = cv::fitEllipse(contours[i]);

		cv::rectangle(src_color, rt.boundingRect(), Scalar(255, 0, 255));
		cv::ellipse(src_color, ellipse, Scalar(0, 255, 0));
		
		Point2f center(0.0);
		float radius = 0;
		cv::minEnclosingCircle(contours[i], center, radius);
		cv::circle(src_color, center, radius, Scalar(255, 255, 255));

		cv::drawMarker(src_color, center, Scalar(0, 255, 255),MarkerTypes::MARKER_TRIANGLE_DOWN);
		cv::drawMarker(src_color, center, Scalar(255,0 , 180), MarkerTypes::MARKER_STAR);

		if (max_length < length) {
			max_index = i;
		}
		{	//Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	/*	Scalar color;
		switch (i)
		{
		case 0: color = Scalar(255, 255, 255);
		case 1: color = Scalar(0, 255, 0);
		case 2: color = Scalar(255, 0, 0);
		default:
			break;
		}

		drawContours(src_color, contours, (int)i, color, 2, LINE_8, hierarchy, 0);*/
		}
	}

	cv::findContours(detect_img_B, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//À±°û¼± ±×¸®±â
	for (size_t i = 0; i < contours.size(); i++)
	{
		double length = cv::arcLength(contours[i], false);
		double area = cv::contourArea(contours[i]);
		RotatedRect rt = cv::minAreaRect(contours[i]);

		if (contours[i].size() < 5) continue;

		RotatedRect ellipse = cv::fitEllipse(contours[i]);

		cv::rectangle(src_color, rt.boundingRect(), Scalar(255, 0, 255));
		cv::ellipse(src_color, ellipse, Scalar(0, 255, 0));

		Point2f center(0.0);
		float radius = 0;
		cv::minEnclosingCircle(contours[i], center, radius);
		cv::circle(src_color, center, radius, Scalar(255, 255, 255));

		cv::drawMarker(src_color, center, Scalar(0, 255, 255), MarkerTypes::MARKER_TRIANGLE_DOWN);
		cv::drawMarker(src_color, center, Scalar(255, 0, 180), MarkerTypes::MARKER_STAR);

		if (max_length < length) {
			max_index = i;
		}
		{	//Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	/*	Scalar color;
		switch (i)
		{
		case 0: color = Scalar(255, 255, 255);
		case 1: color = Scalar(0, 255, 0);
		case 2: color = Scalar(255, 0, 0);
		default:
			break;
		}

		drawContours(src_color, contours, (int)i, color, 2, LINE_8, hierarchy, 0);*/
		}
	}
	drawContours(src_color, contours, (int)max_index, Scalar(255, 255, 255), 2, LINE_8, hierarchy, 0);

	return 1;

}

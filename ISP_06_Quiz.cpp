#pragma once

#include "../Common/Common.h"
#include "ISP.h"

const int max_value_H = 360 / 2;
const int max_value = 255;
const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
static void on_low_H_thresh_trackbar(int, void*)
{
	low_H = min(high_H - 1, low_H);
	setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void*)
{
	high_H = max(high_H, low_H + 1);
	setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void*)
{
	low_S = min(high_S - 1, low_S);
	setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void*)
{
	high_S = max(high_S, low_S + 1);
	setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void*)
{
	low_V = min(high_V - 1, low_V);
	setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void*)
{
	high_V = max(high_V, low_V + 1);
	setTrackbarPos("High V", window_detection_name, high_V);
}

int main1(int argc, char* argv[])
{

	namedWindow(window_capture_name);
	namedWindow(window_detection_name);
	// Trackbars to set thresholds for HSV values
	createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
	createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
	createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
	createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
	createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
	createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
	Mat frame, frame_HSV, frame_threshold;
	string fileDir = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = fileDir + "stop_img.png";
	frame = cv::imread(filename, cv::ImreadModes::IMREAD_COLOR);
	while (true) {

		if (frame.empty())
		{
			break;
		}
		// Convert from BGR to HSV colorspace
		cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
		// Detect the object based on HSV Range Values
		inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
		// Show the frames
		imshow(window_capture_name, frame);
		imshow(window_detection_name, frame_threshold);
		char key = (char)waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}
	}
	return 0;
}
int main() {


	ISP _isp;


	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "stop_img.png";
	Mat src_color = Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));
	//Color RGB -> Convert RGB to HSV
	Mat src_HSV;
	cvtColor(src_color, src_HSV, COLOR_BGR2HSV);

	//Detect Shape
	int low_H = 130;
	int high_H = 180;
	int low_S = 0;
	int high_S = 255;
	int low_V = 0;
	int high_V = 255;

	Scalar lower_R(low_H, low_S, low_V);
	Scalar high_R(high_H, high_S, high_V);
	Mat detect_img_R;
	inRange(src_HSV, lower_R, high_R, detect_img_R);
	//detect_img_R = ~detect_img_R;

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

	//Mat reduced_R = src_color.clone();
	//cvtColor(detect_img_R, detect_img_R, CV_GRAY2BGR);
	//bitwise_or(reduced_R, detect_img_R, reduced_R);
	//cvtColor(detect_img_R, detect_img_R, CV_BGR2GRAY);
	

	//Calc feature

	//À±°û¼± Ã£±â
	RNG rng(12345);
	vector<vector<cv::Point>> contours;
	std::vector< cv::Vec4i> hierarchy;
	cv::findContours(detect_img_R, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	int max_index = 0;
	double max_length = 0;
	//À±°û¼± ±×¸®±â
	for (size_t i = 0; i < contours[i].size(); i++)
	{
		double length = cv::arcLength(contours[i], false);
		double area = cv::contourArea(contours[i]);
		RotatedRect rt = cv::minAreaRect(contours[i]);

		if (contours[i].size() <200) continue;
	

		Point2f center(0,0);
		float radius = 0;
		cv::rectangle(src_color, rt.boundingRect(), Scalar(255, 0, 255));		
	

		cv::drawMarker(src_color, rt.center, Scalar(0, 255, 255), MarkerTypes::MARKER_CROSS,200);
		
		//cv::drawMarker(src_color, rt.center, Scalar(255, 0, 180), MarkerTypes::MARKER_STAR);

		if (max_length < length) {
			max_length = length;
			max_index = i;
		}



	}
	



	return 1;
}

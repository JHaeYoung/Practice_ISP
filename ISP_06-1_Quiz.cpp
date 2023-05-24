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

	namedWindow(window_capture_name,WINDOW_NORMAL);
	namedWindow(window_detection_name, WINDOW_NORMAL);
	// Trackbars to set thresholds for HSV values
	createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
	createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
	createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
	createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
	createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
	createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
	Mat frame, frame_HSV, frame_threshold;
	string fileDir = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = fileDir + "find_google_area.png";
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

	string filePath = "../thirdparty/opencv_470/sources/samples/data/";
	string filename = filePath + "find_google_area.png";
	Mat src_color = Mat(cv::imread(filename, cv::ImreadModes::IMREAD_ANYCOLOR));
	//Color RGB -> Convert RGB to HSV



	Mat src_color_blur;
	blur(src_color, src_color_blur, Size(3, 3));
	Mat src_HSV;
	cvtColor(src_color_blur, src_HSV, COLOR_BGR2HSV);

	//Detect Shape
	int low_H = 0;
	int high_H = 180;
	int low_S = 123;
	int high_S = 255;
	int low_V = 75;
	int high_V = 255;

	Scalar lower_R(low_H, low_S, low_V);
	Scalar high_R(high_H, high_S, high_V);
	Mat detect_img;
	inRange(src_HSV, lower_R, high_R, detect_img);

	//Calc feature
	// 
	//À±°û¼± Ã£±â
	RNG rng(12345);
	vector<vector<cv::Point>> contours;
	std::vector< cv::Vec4i> hierarchy;
	cv::findContours(detect_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	int txt_index = 0;
	int length_spec = 130;

	vector<Rect> vCharROI;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double length = cv::arcLength(contours[i], false);
		double area = cv::contourArea(contours[i]);
		if (area < 10)continue;
		if (length < length_spec) continue;

		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(src_color_blur, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
		
		RotatedRect rt = cv::minAreaRect(contours[i]);
		/*string msg = std::format("[{}]", i);
		putText(src_color_blur, msg, rt.boundingRect().tl(), HersheyFonts::FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 0, 255),1);

		msg = std::format("[{}]-A {}-L {}", i, (int)area, (int)length);
		putText(src_color_blur, msg, Point(10,50+txt_index*20), HersheyFonts::FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 0, 255),1);
		txt_index++;*/
		vCharROI.push_back(rt.boundingRect());
	}
	for (size_t i = 0; i < vCharROI.size(); i++)
	{
		cv::rectangle(src_color_blur, vCharROI[i], Scalar(0, 0, 255));
	}

	int aa = 0;




	int max_index = 0;
	double max_length = 0;
	//À±°û¼± ±×¸®±â
	for (size_t i = 0; i < contours.size(); i++)
	{
		double length = cv::arcLength(contours[i], false);
		double area = cv::contourArea(contours[i]);
		RotatedRect rt = cv::minAreaRect(contours[i]);
		if (contours[i].size() < 55) continue;

		cv::rectangle(src_color, rt.boundingRect(), Scalar(255, 0, 255));
		//cv::drawMarker(src_color, rt.center, Scalar(0, 255, 255), MarkerTypes::MARKER_CROSS, 100);

		if (max_length < length) {
			max_length = length;
			max_index = i;
		}
	}

	return 1;
}

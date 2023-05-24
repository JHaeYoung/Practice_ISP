#include "../Common/Common.h"
#include "ISP.h"


Mat src_gray;
int thresh = 100;
RNG rng(12345);
void thresh_callback(int, void*)
{
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}
	imshow("Contours", drawing);
}
void main()
{
	ISP _isp;
	string fileDir = "../thirdparty/opencv_470/sources/samples/data/";
	string fileName = fileDir + "detect_blob.png";

	Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));
	const char* source_window = "Source";
	namedWindow(source_window);
	imshow(source_window, src);
	const int max_thresh = 255;
	createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey();





	////#1. Convert Color To Gray
	//Mat gray_img = Mat::zeros(height, width, CV_8UC1);
	//uchar* pDataGray = gray_img.data;
	//_isp.Convert_BGR2Gray(pDataColor, width, height, pDataGray);


	//for (size_t i = 0; i < width* height; i++)
	//{
	//	pDataGray[i] < 230 ? pDataGray[i] = 255 : pDataGray[i] = 0;
	//}

	//// À±°û¼± Ã£±â
	//std::vector<std::vector<cv::Point>> contours;
	//std::vector<cv::Vec4i> hierarchy;
	//cv::findContours(gray_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//// À±°û¼± ±×¸®±â
	//RNG rng(12345);
	//cv::Mat contourImage = cv::Mat::zeros(gray_img.size(), CV_8UC3);
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	//	drawContours(contourImage, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

	//	cv::Rect rt = cv::boundingRect(contours[i]);
	//	cv::rectangle(color_img, rt, Scalar(255, 100, 0), 1);
	//}

	//

	//
	//// °á°ú Ãâ·Â
	


	return;
}
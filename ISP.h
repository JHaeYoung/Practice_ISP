#pragma once

#include "../Common/Common.h"


class ISP
{
public:
	ISP();
	~ISP();

	void Convert_BGRtoGray(uchar* pDataBRG, size_t& w, size_t& h, uchar* pY);
	void Get_Histogram(uchar* pDataGray, size_t length, int* pHisto);
	void Get_LPF(uchar* pDataGray, size_t& w, size_t& h, uchar* pDataLPF);
	void Get_HPF1(uchar* pDataGray, size_t& width, size_t& height, uchar* pDataLPF);
	void Get_HPF2(uchar* pDataGray, size_t& width, size_t& height, uchar* pDataLPF);
	void Get_length(uchar* pDataGray, size_t& width, size_t& height);

private:

};


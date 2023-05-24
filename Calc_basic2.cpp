#include "../Common/Common.h"

struct _stResult
{
	int sum = 0;
	double avg = 0.0;
};

void Calc(double* pData, int size, _stResult* pResult) {
	if (pData != nullptr && pResult != nullptr)
	{
		for (size_t i = 0; i < size; i++)
		{
			pResult->sum +=  pData[i];
		}
	 pResult->avg= static_cast<double>( pResult->sum )/ size;
		cout << "ÃÑÇÕÀº : " << pResult->sum << endl;
		cout << "Æò±ÕÀº : " << pResult->avg << endl;
	}
}

int main() {

	//int arr[10] = { 2,9,55,2,3,413,2,3,77,5 };
	double arr[10] = { 2.5,9.1,4.4,2.66,3.48,5.5884,2.412,3.1,4.4,5.7 };

	int sum = 0;
	double avg = 0.0;
	int size = sizeof(arr) / sizeof(arr[0]);

	struct _stResult* SR = new _stResult;
	

	Calc(arr, size, SR);

	cout << "ÃÑÇÕÀº : " << SR->sum << endl;
	cout << "Æò±ÕÀº : " << SR->avg << endl;

	delete SR;

	return 1;
}
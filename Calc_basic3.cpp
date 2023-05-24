#include "../Common/Common.h"

class cResult
{
public:
	
	cResult() { cout << "cResult::ctor" << endl; }
	~cResult() { cout << "cResult::dtor" << endl; }

	void SetSumValue(int _sum) {
		sum = _sum;
	}
	void SetAvgValue(double _avg) {
		avg = _avg;

	}
	void DispSum() {
		cout << "ÃÑÇÕÀº : " << sum << endl;

	}
	void DispAvg() {
		cout << "Æò±ÕÀº : " << avg << endl;

	}

private:
	int sum=0;
	double avg=0.0;
};

void Calc(int* pData, int size, cResult* pResult) {
	int sum = 0;
	double avg = 0.0;
	if (pData != nullptr && pResult != nullptr)
	{
		for (size_t i = 0; i < size; i++)
		{
			sum += pData[i];
		}
		avg = static_cast<double>(sum) / size;
		pResult->SetSumValue(sum);
		pResult->SetAvgValue(avg);
	}

}

int main() {

	int arr[10] = { 2,9,55,2,3,413,2,3,77,5 };
	//double arr[10] = { 2.5,9.1,4.4,2.66,3.48,5.5884,2.412,3.1,4.4,5.7 };

	int size = sizeof(arr) / sizeof(arr[0]);	

	cResult* CR = new cResult();

	Calc(arr, size, CR);
	CR->DispSum();
	CR->DispAvg();

	delete CR;

	return 1;
}
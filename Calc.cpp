#include "../Common/Common.h"
//int* sum  = int Ÿ���� �ּҸ� sum�̶�� ������ ����
//int *sum  = int Ÿ���� *sum�̶�� ������ ����

void Calc(double* pData, int size, int* sum, double* avg) {
	//       start       ũ��      
	/*int _sum = 0;
	double _avg = 0.0;
	for (size_t i = 0; i < size; i++)
	{
		_sum = _sum + pData[i];
	}
	_avg = (double)_sum / size;

	*sum = _sum;
	*avg = _avg;*/


	for (size_t i = 0; i < size; i++)
	{
		*sum =*sum + pData[i];
	}
	*avg = (double)*sum/ size;
	cout << "������ : " << *sum << endl;
	cout << "����� : " << *avg << endl;

}

int main() {

	//int arr[10] = { 2,9,4,2,3,5,2,3,4,5 };
	double arr[10] = { 2.5,9.1,4.4,2.66,3.48,5.5884,2.412,3.1,4.4,5.7 };

	int sum=0;
	double avg=0.0;
	int size = sizeof(arr) / sizeof(arr[0]);

	Calc(arr, size, &sum, &avg);

	cout << "������ : " << sum << endl;
	cout << "����� : " << avg << endl;

	return 1;
}
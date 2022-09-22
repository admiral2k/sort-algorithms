#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
using namespace std;

//GLOBAL VARIABLES

//consts
const int numOfTests = 5;

// initialization of set of 0 for results

int lengthList[numOfTests] = { 10000, 30000, 90000, 270000, 810000 };

//FUNCTIONS

vector<int> createRandArray(int length)
{
	vector<int> randArray;
	for (int i = 0; i < length; i++)
	{
		randArray.push_back(rand() % 65535);
	}
	return randArray;
}

//that function returns time spended to sort.
void timeSpend(vector<int> arr, int length, void (*func)(vector<int>, int))
{
	clock_t start = clock();    //start time initialization
	func(arr, length);
	clock_t stop = clock();     //end time initialization
	cout << "Spended " << (stop - start) / (float)(CLOCKS_PER_SEC) << " seconds.\n\n";
}


void bubbleSort(vector<int> m, int n) {
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++) {
			if (m[j] > m[j + 1]) {
				int bf = m[j];
				m[j] = m[j + 1];
				m[j + 1] = bf;
			}
		}
	}
}

void merge(vector<int>& arr1, vector<int>& arr2)
{
	vector<int> arr3;
	int pointer1 = 0;
	int pointer2 = 0;
	int endArr = 0;

	for (int i = 0; i < arr1.size() + arr2.size(); i++)
	{
		if (arr1[pointer1] < arr2[pointer2])
		{
			arr3.push_back(arr1[pointer1]);
			pointer1++;
			if (pointer1 == arr1.size())
			{
				endArr = 1;
				break;
			}
		}
		else
		{
			arr3.push_back(arr2[pointer2]);
			pointer2++;
			if (pointer2 == arr2.size())
			{
				endArr = 2;
				break;
			}
		}
	}
	if (endArr == 1)
	{
		for (int i = pointer2; i < arr2.size(); i++)
		{
			arr3.push_back(arr2[i]);
		}
	}
	else if (endArr == 2)
	{
		for (int i = pointer1; i < arr1.size(); i++)
		{
			arr3.push_back(arr1[i]);
		}
	}
	arr1 = arr3;
}

vector<int> mergeSort(vector <int>& arr, int length)
{
	if (arr.size() == 1)
	{
		return arr;
	}
	int m = length / 2;
	vector<int> rightArr;
	vector<int> leftArr;
	for (int i = 0; i < length; i++)
	{
		if (i >= m)
			rightArr.push_back(arr[i]);
		else
		{
			leftArr.push_back(arr[i]);
		}
	}

	leftArr = mergeSort(leftArr, m);
	rightArr = mergeSort(rightArr, length - m);
	merge(leftArr, rightArr);
	return leftArr;
}

void mergeSortFunc(vector<int> arr, int length)
{
	mergeSort(arr, length);
};

void radixSort(vector<int> arr, int length)
{
	int n = 5;
	vector<vector<int>> buff;
	int var1;
	int var2;
	for (int i = 0; i < length; i++)
	{
		buff.push_back({});
	}
	for (int i = 0; i < n; i++)
	{
		var1 = (pow(10, i + 1));
		var2 = (pow(10, i));
		for (int j = 0; j < length; j++)
		{
			buff[(arr[j] % var1) / var2].push_back(arr[j]);
		}
		arr = {};
		for (int d = 0; d < length; d++)
		{
			for (int b = 0; b < buff[d].size(); b++)
			{
				arr.push_back(buff[d][b]);
			}
		}
		buff = {};
		for (int i = 0; i < length; i++)
		{
			buff.push_back({});
		}
	}
}


int main() 
{
	//randomization setup
	srand(time(0));

	for (int i = 0; i < numOfTests; i++)
	{
		cout << "--------------------\n" << lengthList[i] << " ELEMENTS TEST\n--------------------\n";
		//creating random array with length from lengthList
		vector<int> randArray = createRandArray(lengthList[i]);

		//writing down time the function spend for sorting
		//cout << "Bubble sort:\n";
		//timeSpend(randArray, lengthList[i], &bubbleSort);

		//writing down time the function spend for sorting
		cout << "Merge sort sort:\n";
		timeSpend(randArray, lengthList[i], &mergeSortFunc);

		//writing down time the function spend for sorting
		cout << "Radix sort:\n";
		timeSpend(randArray, lengthList[i], &radixSort);
	}
	return 0;
}
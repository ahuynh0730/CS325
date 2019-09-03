/*******************************************************************************
** Author:       Anthony Huynh
** Date:         4/14/201
** Description:  checking to see how long to sort using stoogeSort
*******************************************************************************/


#include <utility>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>



void stoogeSort(int array[], int beginning, int end) {

	if (beginning > end) {
		return;
	}

	//sets n to size of array, will swap if n is 22 and first element is larger than second
	int n = end - beginning + 1;
	if ((n == 2) && (array[beginning] > array[end])) {
		std::swap(array[beginning], array[end]);
	}

	//sets m to ceiling of 2n/3 and recursively calls stoogeSort
	else if (n > 2) {
		int m = ceil(2.0 * n / 3.0);
		stoogeSort(array, beginning, beginning + m - 1);
		stoogeSort(array, end - m + 1, end);
		stoogeSort(array, beginning, beginning + m - 1);
	}

}

int main() {
	srand(time(NULL));

	//gets array size from user
	int arraySize;
	std::cout << "How big would you like the array size to be? ";
	std::cin >> arraySize;

	//dynamically creates array and fills with numbers between 0 and 10000
	int *myArray = new int[arraySize];
	for (int i = 0; i < arraySize; i++) {
		myArray[i] = rand() % 10001;
	}

	//starts clock and displays time after sorting
	clock_t timer = clock();
	stoogeSort(myArray, 0, arraySize - 1);
	timer = clock() - timer;
	std::cout << arraySize << " integers sorted in " << (float)timer / (float)CLOCKS_PER_SEC << " seconds." << std::endl;

	delete myArray;

	return 0;
}
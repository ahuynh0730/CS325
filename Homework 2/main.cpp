/*******************************************************************************
** Author:       Anthony Huynh
** Date:         4/14/201
** Description:  implentation of stoogeSort
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <utility>
#include <math.h>



void stoogeSort(int array[], int beginning, int end){

	if (beginning > end) {
		return;
	}

	//sets n to size of array, will swap if n is 22 and first element is larger than second
	int n = end - beginning + 1;
	if ((n == 2) && (array[beginning] > array[end]) ) {
		std::swap(array[beginning], array[end]);
	}

	//sets m to ceiling of 2n/3 and recursively calls stoogeSort
	else if (n > 2) {
		int m = ceil(2.0 * n / 3.0);
		stoogeSort(array, beginning, beginning + m - 1);
		stoogeSort(array, end - m + 1 , end);
		stoogeSort(array, beginning, beginning + m - 1);
	}

}

int main() {

	//opens input/output files
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open("data.txt");
	outputFile.open("stooge.out");

	//display messages if files are not open
	if (!outputFile.is_open()) {
		std::cout << "Unable to open output file" << std::endl;
	}
	if (!inputFile.is_open()){
		std::cout << "Unable to open input file" << std::endl;
	}


	//will take first number and set as array size, then read each number to fill array until array size is reached
	//after inputting into array, will call stoogeSort and then write to file
	//will repeat for each new line
	else {
		while (!inputFile.eof()) {
			int arraySize;
			inputFile >> arraySize;
			int* myArray = new int[arraySize];
			for (int i = 0; i < arraySize; i++)
			{
				inputFile >> myArray[i];
			}

			stoogeSort(myArray, 0, arraySize - 1);
			for (int i = 0; i < arraySize; i++) {
				outputFile << myArray[i];
			}
			outputFile << std::endl;

			delete myArray;
		}
	}
	inputFile.close();
	outputFile.close();


	return 0;
}
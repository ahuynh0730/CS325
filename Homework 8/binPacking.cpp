/*******************************************************************************
** Author:       Anthony Huynh
** Date:         6/3/2019
** Description:  code for bin packing problem
*******************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

bool greaterThan(int i, int j) {
	return (i > j);
}

//will loop through each item
//if item exceeds capacity, will move to next bin, if it is the final bin, will open a new bin
//if item can be added to bin, items weight will be added to the bins weight and move to the next item
void firstFit(std::vector<int> listOfItems, std::vector<int> &bins, int binCapacity) {
	for (unsigned int i = 0; i < listOfItems.size(); i++) {
		for (unsigned int j = 0; j < bins.size(); j++) {
			if (listOfItems[i] + bins[j] > binCapacity) {
				if (j == bins.size() - 1) {
					bins.push_back(0);
				}
			}
			else {
				bins[j] += listOfItems[i];
				break;
			}
		}
	}
}

int main() {

	//opening file
	std::ifstream inFile;
	std::string fileName;
	std::cout << "Please enter the name of the input file: ";
	std::cin >> fileName;
	
	inFile.open(fileName);
	if (!inFile.is_open()) {
		std::cout << "Was not able to open file!" << std::endl;
		return 1;
	}

	//getting number of test cases from file
	int numberTestCases = 0;
	inFile >> numberTestCases;


	for (int k = 0; k < numberTestCases; k++) {

		//getting bin capacity
		int binCapacity = 0;
		inFile >> binCapacity;

		//getting total number of items
		int numberItems = 0;
		inFile >> numberItems;

		//vector used to hold each items' weights
		std::vector<int> itemWeights;
		for (int i = 0; i < numberItems; i++) {
			int weightOfItem;
			inFile >> weightOfItem;
			itemWeights.push_back(weightOfItem);
		}


		//First fit
		//calls first fit

		//vector of ints that hold current weight for first fit
		std::vector<int> firstFitBins;
		firstFitBins.push_back(0);

		clock_t firstFitTimer = clock();
		firstFit(itemWeights, firstFitBins, binCapacity);
		firstFitTimer = clock() - firstFitTimer;

		//Best Fit
		//goes through each item making the smallestLeftover 1 over the capacity and the binWithSmallestLeftover 1 over the amount of items
		//goes through each bin, seeing if would leave with smallest leftover
		//if all bins are searched and leftover is greater than capacity, will create new bin and sets bin number to the size -1
		//adds weight of item to binWithSmallestLeftover
		clock_t bestFitTimer = clock();
		std::vector<int> bestFitBins;
		bestFitBins.push_back(0);
		for (int i = 0; i < numberItems; i++) {
			int smallestLeftover = binCapacity + 1;
			int binWithSmallestLeftover = numberItems + 1;
			for (unsigned int j = 0; j < bestFitBins.size(); j++) {
				if (bestFitBins[j] + itemWeights[i] < smallestLeftover) {
					smallestLeftover = binCapacity - bestFitBins[j] - itemWeights[i];
					binWithSmallestLeftover = j;
				}
			}
			if (smallestLeftover > binCapacity){
				bestFitBins.push_back(0);
				binWithSmallestLeftover = bestFitBins.size() - 1;
			}
			bestFitBins[binWithSmallestLeftover] += itemWeights[i];
		}
		bestFitTimer = clock() - bestFitTimer;

		//First-Fit Decreasing
		//will sort items on weight, then call first fit
		std::vector<int> firstFitDecreasingBins;
		firstFitDecreasingBins.push_back(0);
		clock_t firstFitDecreasingTimer = clock();
		std::sort(itemWeights.begin(), itemWeights.end(), greaterThan);
		firstFit(itemWeights, firstFitDecreasingBins, binCapacity);
		firstFitDecreasingTimer = clock() - firstFitDecreasingTimer;


		//output
		std::cout << "Test case " << k + 1 << " First Fit: " << firstFitBins.size() << ", " 
			<< (float)firstFitTimer / (float)CLOCKS_PER_SEC << " seconds. First Fit Decreasing: "
			<< firstFitDecreasingBins.size() <<", "<< (float)firstFitDecreasingTimer / (float)CLOCKS_PER_SEC
			<< " seconds. Best Fit: " << bestFitBins.size() << ", " <<(float)bestFitTimer / (float)CLOCKS_PER_SEC
			<< " seconds." << std::endl;
	}

	inFile.close();
	return 0;
}

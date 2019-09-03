/*******************************************************************************
** Author:       Anthony Huynh
** Date:         4/21/201
** Description:  code for 0/1 Knapsack Problem
*******************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>




int knapsack(int[], int[], int, int);



int main() {
	int T;		//number of test cases
	int N;		//number of items
	int P[100];	//prices of items
	int W[100];	//weights of items
	int F;		//amount of people in family
	int M = 0;	//max weight that can be carried

	std::ifstream inFile;
	std::ofstream outputFile;
	outputFile.open("results.txt");
	inFile.open("shopping.txt");
	if (!inFile.is_open() || !outputFile.is_open()) {
		std::cout << "Was not able to open file!" << std::endl;
		return 1;
	}

	inFile >> T;
	for (int i = 0; i < T; i++) {
		//to indicate how many lines are items
		inFile >> N;

		//to insert weights and price
		for (int j = 0; j < N; j++) {
			inFile >> P[j];
			inFile >> W[j];
		}

		int totalFamilyPrice = 0;

		//to indicate how many family members there are
		inFile >> F;

		//to cycle through each family member and determine max profit using maximum items
		for (int j = 0; j < F; j++) {
			inFile >> M;
			totalFamilyPrice = totalFamilyPrice + knapsack(W, P, N, M);
		}

		outputFile << "Test Case " << i + 1 << std::endl;
		outputFile << "Total Price " << totalFamilyPrice << std::endl;
		

	}

	


	outputFile.close();
	inFile.close();
	return 0;
}

int knapsack(int W[], int P[], int N, int M) {
	int ** K = new int*[N + 1];
	for (int i = 0; i < N + 1; i++) {
		K[i] = new int[M + 1];
	}

	for (int i = 0; i < N+1; i++) {
		for (int w = 0; w < M+1; w++) {
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (W[i - 1] <= w)
				K[i][w] = std::max(P[i - 1] + K[i - 1][w - W[i - 1]], K[i - 1][2]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	int numberToReturn = K[N][M];
	int w = M;


	for (int i = 0; i < N + 1; i++) {
		delete K[i];
	}
	delete K;

	return numberToReturn;
}
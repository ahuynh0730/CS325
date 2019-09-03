/*******************************************************************************
** Author:       Anthony Huynh
** Date:         4/28/2019
** Description:  code for last to start problem
*******************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<vector>

// Driver function to sort the vector elements 
// by second element of pairs
// modified from geeksforgeeks
bool sortByEndTime(const std::pair<int, std::pair<int, int>> &a,
	const std::pair<int, std::pair<int, int>> &b) {
	return (a.second.second < b.second.second);
}

int main() {

	//opening file
	std::ifstream inFile;
	inFile.open("act.txt");
	if (!inFile.is_open()) {
		std::cout << "Was not able to open file!" << std::endl;
		return 1;
	}

	int setNumber = 0;
	while (!inFile.eof()) {

		//increases set number upon entering loop, and reads in amount of activities for the set
		setNumber++;
		int amountOfActivities;
		inFile >> amountOfActivities;


		//vector used to store activity number, start time, and end time
		std::vector<std::pair<int, std::pair<int, int>>> activitiesVector;

		//to read in number of activity, start time, and end time and add to vector
		for (int i = 0; i < amountOfActivities; i++) {
			int activityNumber, startTime, endTime;
			inFile >> activityNumber >> startTime >> endTime;
			activitiesVector.push_back(std::make_pair(activityNumber, std::make_pair(startTime, endTime)));
		}

		//sorting vector based on end time
		std::sort(activitiesVector.begin(), activitiesVector.end(), sortByEndTime);

		//vector to hold activity numbers that are selected
		std::vector<int> selectedActivities;
		
		//adds last activity to vector
		selectedActivities.push_back(activitiesVector[amountOfActivities - 1].first);
		int last = amountOfActivities - 1;

		//starts from bottom and adds to selected vector if end time is less than or equal to start time
		for (int i = amountOfActivities - 2; i >= 0; i--) {
			if (activitiesVector[i].second.second <= activitiesVector[last].second.first) {
				selectedActivities.push_back(activitiesVector[i].first);
				last = i;
			}
		}

		//output messages
		std::cout << "Set " << setNumber << std::endl;
		std::cout << "Number of activities selected = " << selectedActivities.size() << std::endl;
		std::cout << "Activities: ";
		for (unsigned int i = 0; i < selectedActivities.size(); i++) {
			std::cout << selectedActivities[i] << " ";
		}
		std::cout << std::endl;
		
		
	}

	return 0;
}
/*******************************************************************************
** Author:       Anthony Huynh
** Date:         5/12/2019
** Description:  code for babyface and heels wrestler problem
*******************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>


struct Node;
struct Edge;

struct Edge {
	Node* destination1;
	Node* destination2;
	bool wasTraversed = false;
};

struct Node
{
	std::string name;
	std::vector<Edge> edges;
	bool hasTeam = false;
	bool isBabyFace = false;
	bool isHeel = false;
};

int main() {

	std::ifstream inFile;
	std::string fileName;
	std::cout << "Please enter the name of the input file: ";
	std::cin >> fileName;

	
	inFile.open(fileName);
	if (!inFile.is_open()) {
		std::cout << "Was not able to open file!" << std::endl;
		return 1;
	}

	std::vector<Node> graphWrestlers;

	//to get the number of wrestlers from the file
	int numberWrestlers = 0;
	inFile >> numberWrestlers;


	//to insert each name as a node in the graph
	for (int i = 0; i < numberWrestlers; i++) {
		graphWrestlers.push_back(Node());
		inFile >> graphWrestlers[i].name;
	}


	//to get number of rivalries from file
	int numberRivalries;
	inFile >> numberRivalries;

	std::string wrestler1;
	std::string wrestler2;


	//reading in rivalries and creating edges between the nodes
	for (int i = 0; i < numberRivalries; i++) {
		inFile >> wrestler1;
		inFile >> wrestler2;
		int wrestler1Position = -1;
		int wrestler2Position = -1;

		for (unsigned int i = 0; i < graphWrestlers.size(); i++) {
			if (wrestler1 == graphWrestlers[i].name) {
				wrestler1Position = i;
			}
			if (wrestler2 == graphWrestlers[i].name) {
				wrestler2Position = i;
			}
		}
		
		//creates edge between nodes
		graphWrestlers[wrestler1Position].edges.push_back(Edge());
		int currentEdgeA = graphWrestlers[wrestler1Position].edges.size() - 1;
		graphWrestlers[wrestler1Position].edges[currentEdgeA].destination1 = &graphWrestlers[wrestler1Position];
		graphWrestlers[wrestler1Position].edges[currentEdgeA].destination2 = &graphWrestlers[wrestler2Position];

		//will use the same edge created above instead of making a new edge
		graphWrestlers[wrestler2Position].edges.push_back(Edge());
		int currentEdgeB = graphWrestlers[wrestler2Position].edges.size() - 1;
		graphWrestlers[wrestler2Position].edges[currentEdgeB] = graphWrestlers[wrestler1Position].edges[currentEdgeA];
	}
	inFile.close();

	//to make the first wrestler in the list a babyface
	graphWrestlers[0].hasTeam = true;
	graphWrestlers[0].isBabyFace = true;
	Node* currentNode = &graphWrestlers[0];
	Node* nextNode = &graphWrestlers[0];;

	for (int edgesTraveled = 0; edgesTraveled < numberRivalries * 2; edgesTraveled++) {
		//to loop through each edge for each wrestler
		currentNode = nextNode;
		for (unsigned int j = 0; j < currentNode->edges.size(); j++) {
			//will only check an edge if it was not checked due to a prior node
			if (currentNode->edges[j].wasTraversed == false) {
				bool isDestination1 = false;
				if (currentNode->edges[j].destination1 == currentNode) {
					isDestination1 = true;
				}

				//only if the current node is the first name listed in a pair of rivalry
				if (isDestination1) {
					nextNode = currentNode->edges[j].destination2;
					//if the second name listed in the pair does not have a team yet, will assign one
					if (currentNode->edges[j].destination2->hasTeam == false) {
						if (currentNode->edges[j].destination1->isBabyFace == true) {
							currentNode->edges[j].destination2->isHeel = true;
							currentNode->edges[j].destination2->hasTeam = true;
						}
						if (currentNode->edges[j].destination1->isHeel == true) {
							currentNode->edges[j].destination2->isBabyFace = true;
							currentNode->edges[j].destination2->hasTeam = true;
						}

						currentNode->edges[j].wasTraversed = true;
					}
					//will exit if rivalry exists between two wrestlers of the same team
					else {
						if (currentNode->edges[j].destination1->isBabyFace == currentNode->edges[j].destination2->isBabyFace) {
							std::cout << "This is not possible." << std::endl;
							return 0;
						}
					}
				}
				//if the current node is the second name listed in the rivalry
				else {
					nextNode = currentNode->edges[j].destination1;
					if (currentNode->edges[j].destination1->hasTeam == false) {
						if (currentNode->edges[j].destination2->isBabyFace == true) {
							currentNode->edges[j].destination1->isHeel = true;
							currentNode->edges[j].destination1->hasTeam = true;
						}
						if (currentNode->edges[j].destination2->isHeel == true) {
							currentNode->edges[j].destination1->isBabyFace = true;
							currentNode->edges[j].destination1->hasTeam = true;
						}
						currentNode->edges[j].wasTraversed = true;
					}
					//will exit if rivalry exists between two wrestlers of the same team
					else {
						if (currentNode->edges[j].destination1->isBabyFace == currentNode->edges[j].destination2->isBabyFace) {
							std::cout << "This is not possible." << std::endl;
							return 0;
						}
					}
				}
			}
		}
		
	}
	

	//for any wrestlers that can be on either team
	for (unsigned int i = 0; i < graphWrestlers.size(); i++) {
		if (!graphWrestlers[i].hasTeam) {
			graphWrestlers[i].isBabyFace = true;
			graphWrestlers[i].hasTeam = true;
			bool isDestination1 = false;
			for (unsigned int j = 0; j < graphWrestlers[i].edges.size(); j++) {
				if (graphWrestlers[i].edges[j].destination1 == &graphWrestlers[i]) {
					isDestination1 = true;
				}
				
				if (isDestination1) {
					graphWrestlers[i].edges[j].destination2->isHeel = true;
				}
				else {
					graphWrestlers[i].edges[j].destination1->isHeel = true;
				}
				graphWrestlers[i].edges[j].destination2->hasTeam = true;

			}
		}
	}

	//outputting the teams
	std::cout << "Yes" << std::endl;
	std::cout << "Babyfaces: ";
	for (unsigned int i = 0; i < graphWrestlers.size(); i++) {
		if (graphWrestlers[i].isBabyFace == true) {
			std::cout << graphWrestlers[i].name << " ";
		}
	}
	std::cout << std::endl << "Heels: ";
	for (unsigned int i = 0; i < graphWrestlers.size(); i++) {
		if (graphWrestlers[i].isHeel == true) {
			std::cout << graphWrestlers[i].name << " ";
		}
	}
	std::cout << std::endl;







	
	return 0;
}
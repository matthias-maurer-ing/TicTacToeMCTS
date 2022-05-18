#pragma once
#include <vector>
#include <iostream>

/*
* A Node represents an Element of the Monte Carlo Tree:
* ParentPointer, which points to the corresponding parent Node. The parentPointer of the root Node points nowhere.
* 
* When a node is created, the gameState is evaluated and each possible action that can be taken gets added to this vector
* even if the action would result in a defeat. This means in the first round there are 9 actions left in the second 8 actions and so on..
* 
* If it comes to an expansion at the current node, the function MCTSExpansion() selects the first element of the actionsLeft vector
* and creates a new nodeElement, and saves the Pointer poiting to it into childrenPointer.
* 
* There is a copy of the current gameState saved in each Node as well as some of its primitive data.
* 
*/

//Data from Main.cpp
extern bool c_mainTurnIndex;

class NodeElement {
public:
	//Non-primitive Data
	NodeElement* parentPointer; 
	std::vector<int> actionsLeft; 
	std::vector<NodeElement*> childrenPointer;
	int* currentGameState;

	//Primitive Data
	int visitingCount;
	float uctValue;
	float reward;
	bool nodeTurnIndex;
	bool isRootNode;
	int Generation;

	//Constructor RootNode
	NodeElement(int* gameStateArray) {
		parentPointer = NULL;
		visitingCount = 0;
		uctValue = 0;
		reward = 0;
		nodeTurnIndex = true;
		isRootNode = true;
		Generation = 0;

		currentGameState = new int[9]{ 0 };
		for (int i = 0; i < 9; i++) { currentGameState[i] = gameStateArray[i]; }
		for (int i = 0; i < 9; i++) { if (currentGameState[i] == 0) { actionsLeft.push_back(i); } }

	}
	//Constructor !RootNode
	NodeElement(NodeElement* nodeElement, int overrideIndex) {
		visitingCount = 0;
		uctValue = 0;
		reward = 0;
		nodeTurnIndex = !nodeElement->nodeTurnIndex;
		isRootNode = c_mainTurnIndex;
		Generation = nodeElement->Generation + 1;

		parentPointer = nodeElement;
		//Erstelle eine neue currentGameState instanz irgendwo anders im Speicher und überschreibe mit ausgewählter Aktion am Index n
		currentGameState = new int[9]{ 0 };
		for (int i = 0; i < 9; i++) { currentGameState[i] = nodeElement->currentGameState[i]; }
		if (nodeTurnIndex) { currentGameState[overrideIndex] = 1; }
		else if (!nodeTurnIndex) { currentGameState[overrideIndex] = -1; }
		for (int i = 0; i < 9; i++) { if (currentGameState[i] == 0) { actionsLeft.push_back(i); } }

	}

	//Deconstructor
	~NodeElement() {
		delete[] currentGameState;
	}
};
//********************************BaselineFunctions********************************
void PrintGameState(int* currentGameState);
int FindBestUCTChildIndex(NodeElement& nodeElement);
int FindBestRewardChildIndex(NodeElement& nodeElement);
float CalcReward(int* currentGameState);
int CalcRewardAssistance(int l, int m, int n, int* currentGameState);
bool HasGameEnded(int* currentGameState);
bool HasGameEndedAssistance(int l, int m, int n, int* currentGameState);

//********************************MCTSFunctions********************************
void MCTSSelection(NodeElement& nodeElement);
void MCTSExpansion(NodeElement& nodeElement);
void MCTSSimulation(NodeElement& nodeElement);
void MCTSBackpropagation(NodeElement& nodeElement, float reward);
void DestroyMCTSTree(NodeElement* nodeElement);

//********************************MainFunction********************************
enum GameState {
	MainMode,
	AIMode,
	PlayerMode
};
void MainMenu();
void AIMenu();
void PlayerMenu();
void MCTSMode();
void DisplayCurrentResults();
void DisplayAllResults();

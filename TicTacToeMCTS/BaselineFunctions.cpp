#include "Header.h"

//Data from Main.cpp
extern float c_explorationValue;

//Prints the current GameState to the console
void PrintGameState(int* currentGameState) {
	//std::cout << "*****" << std::endl;
	for (int i = 6; i < 9; i++) {
		if (currentGameState[i] == 1) { std::cout << "x "; }
		if (currentGameState[i] == 0) { std::cout << "+ "; }
		if (currentGameState[i] == -1) { std::cout << "o "; }
		if ((i + 1) % 3 == 0) { std::cout << std::endl; }
	}
	for (int i = 3; i < 6; i++) {
		if (currentGameState[i] == 1) { std::cout << "x "; }
		if (currentGameState[i] == 0) { std::cout << "+ "; }
		if (currentGameState[i] == -1) { std::cout << "o "; }
		if ((i + 1) % 3 == 0) { std::cout << std::endl; }
	}
	for (int i = 0; i < 3; i++) {
		if (currentGameState[i] == 1) { std::cout << "x "; }
		if (currentGameState[i] == 0) { std::cout << "+ "; }
		if (currentGameState[i] == -1) { std::cout << "o "; }
		if ((i + 1) % 3 == 0) { std::cout << std::endl; }
	}
}

//Returns Index of Child with highest UCT Value at the current nodeElement
int FindBestUCTChildIndex(NodeElement& nodeElement) { 
	int currentMaxUCTIndex = 0;
	int currentMaxUCTValue;
	for (int i = 0; i < nodeElement.childrenPointer.size(); i++) {
		nodeElement.childrenPointer[i]->uctValue = nodeElement.childrenPointer[i]->reward / nodeElement.childrenPointer[i]->visitingCount + c_explorationValue * sqrt(log((nodeElement.visitingCount) / (nodeElement.childrenPointer[i]->visitingCount)));
		currentMaxUCTValue = nodeElement.childrenPointer[0]->uctValue;
		if (nodeElement.childrenPointer[i]->uctValue > currentMaxUCTValue) {
			currentMaxUCTIndex = i; currentMaxUCTValue = nodeElement.childrenPointer[i]->uctValue;
		}
	}
	return currentMaxUCTIndex;
}

//Returns Index of Child with highest Reward Value at the current nodeElement
int FindBestRewardChildIndex(NodeElement& nodeElement) {
	int currentMaxRewardIndex = 0;
	int currentMaxRewardValue = nodeElement.childrenPointer[0]->reward;
	for (int i = 0; i < nodeElement.childrenPointer.size(); i++) {
		if (nodeElement.childrenPointer[i]->reward > currentMaxRewardValue) {
			currentMaxRewardIndex = i; currentMaxRewardValue = nodeElement.childrenPointer[i]->reward;
		}
	}
	return currentMaxRewardIndex;
}

//Calculates the reward by analyzing the currentGameState
float CalcReward(int* currentGameState) {
		float reward = 0;

		if (HasGameEndedAssistance(0, 1, 2, currentGameState)) {reward = CalcRewardAssistance(0, 1, 2, currentGameState);}
		if (HasGameEndedAssistance(3, 4, 5, currentGameState)) {reward = CalcRewardAssistance(3, 4, 5, currentGameState);}
		if (HasGameEndedAssistance(6, 7, 8, currentGameState)) {reward = CalcRewardAssistance(6, 7, 8, currentGameState);}
		if (HasGameEndedAssistance(0, 3, 6, currentGameState)) {reward = CalcRewardAssistance(0, 3, 6, currentGameState);}
		if (HasGameEndedAssistance(1, 4, 7, currentGameState)) {reward = CalcRewardAssistance(1, 4, 7, currentGameState);}
		if (HasGameEndedAssistance(2, 5, 8, currentGameState)) {reward = CalcRewardAssistance(2, 5, 8, currentGameState);}
		if (HasGameEndedAssistance(0, 4, 8, currentGameState)) {reward = CalcRewardAssistance(0, 4, 8, currentGameState);}
		if (HasGameEndedAssistance(2, 4, 6, currentGameState)) {reward = CalcRewardAssistance(2, 4, 6, currentGameState);}
	
		return reward;
}

//Assistance function, if the player scores 3 in row a negative reward is induced, because the AI looses, and vice versa.
int CalcRewardAssistance(int l, int m, int n, int* currentGameState) { //Function that takes in game positions and returns true if there are three in a line
	if (currentGameState[l] == 1 && currentGameState[m] == 1 && currentGameState[n] == 1) {
		return -1;
	}
	if (currentGameState[l] == -1 && currentGameState[m] == -1 && currentGameState[n] == -1) {
		return 1;
	}
	else return 0;
}

//Checks if the game in the current state has ended, returns true if it ended. 
bool HasGameEnded(int* currentGameState) {
	bool hasGameEnded = true;
	for (int i = 0; i < 9; i++) {
		if (currentGameState[i] == 0) hasGameEnded = false;
	}
	if (HasGameEndedAssistance(0, 1, 2, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(3, 4, 5, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(6, 7, 8, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(0, 3, 6, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(1, 4, 7, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(2, 5, 8, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(0, 4, 8, currentGameState)) { hasGameEnded = true; }
	if (HasGameEndedAssistance(2, 4, 6, currentGameState)) { hasGameEnded = true; }

	return hasGameEnded;
}

//Assistance function, checks if the 3 symbols in a row are all of the same type. So that xxo for example doesnt end the game.
bool HasGameEndedAssistance(int l, int m, int n, int* currentGameState) {
	if ((currentGameState[l] == 1 && currentGameState[m] == 1 && currentGameState[n] == 1) || (currentGameState[l] == -1 && currentGameState[m] == -1 && currentGameState[n] == -1)) {
		return true;
	}
	else return false;
}




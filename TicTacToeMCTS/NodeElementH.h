#pragma once
#include "Header.h"
#include <vector>
#include <iostream>

class NodeElement {
public:	
	NodeElement* parentPointer; //Pointer pointing to parent NodeElement, initialized at creation
	std::vector<NodeElement*> childrenPointerArray; //Array of Pointers Pointing to children NodeElement, starts empty grows with children
	std::vector<int> actionsLeft;
	int *currentGameState;

	int visitingCount;
	float uctValue;
	float reward;
	bool isPlayersTurn;
	bool isRootNode;

	NodeElement(int* gameStateArray) {
		parentPointer = 0;
		for (int i = 0; i < 9; i++) { if (currentGameState[i] == 0) { actionsLeft.push_back(i); } }
		currentGameState = new int[9]{0};
		for (int i = 0; i < 9; i++) { currentGameState[i] = gameStateArray[i]; }

		visitingCount = 0;
		uctValue = 0;
		reward = 0;
		isPlayersTurn = false;
		isRootNode = true;
	}

	NodeElement(NodeElement* nodeElement, int overrideIndex) {
		parentPointer = nodeElement;
		for (int i = 0; i < 9; i++) {if (currentGameState[i] == 0) { actionsLeft.push_back(i); }}
		//Erstelle eine neue currentGameState instanz irgendwo anders im Speicher und überschreibe mit ausgewählter Aktion am Index n
		currentGameState = new int[9]{ 0 };
		for (int i = 0; i < 9; i++) {currentGameState[i] = nodeElement->currentGameState[i];}
		if (isPlayersTurn) { currentGameState[overrideIndex] = 1; }
		else if (!isPlayersTurn) { currentGameState[overrideIndex] = -1; }

		visitingCount = 0;
		uctValue = 0;
		reward = 0;
		isPlayersTurn = !nodeElement->isPlayersTurn;
		isRootNode = false;
	}
};
#include "Header.h"

/*
* Selection
* If current gameState has not ended yet: 
* Create an expansion if there are any actions left in the current node
* or select the best child by the UCT criteria.
* 
* If the current gameState is a terminal node, do a simulation and backpropagate the reward.
*/
void MCTSSelection(NodeElement& nodeElement) {
	if (!HasGameEnded(nodeElement.currentGameState)) {
		if (nodeElement.actionsLeft.size() > 0) { MCTSExpansion(nodeElement); }
		else { MCTSSelection(*nodeElement.childrenPointer[FindBestUCTChildIndex(nodeElement)]); }
	}
	else MCTSSimulation(nodeElement);
}

/*
* Expansion
* Get the first element from the actionList of the current node. The action describes the Index at which the next move will take place.
* After the index has been copied to actionIndex delete the entry from the actionsLeft vector.
* Create a new NodeElement and place the next move at the actionIndex.
* Add the adress of this new NodeElement to the childrenPointerArray of the current nodeElement.
* Do a simulation wv the new child nodeElement.
*/
void MCTSExpansion(NodeElement& nodeElement) {
	int actionIndex = nodeElement.actionsLeft[0];
	nodeElement.actionsLeft.erase(nodeElement.actionsLeft.begin());

	NodeElement* expandedChild = new NodeElement(&nodeElement, actionIndex);
	nodeElement.childrenPointer.push_back(expandedChild);
	MCTSSimulation(*expandedChild);
}

/*
* Simulation
* Create a copy of the gameState from the current NodeElement.
* Then each player takes random actions until the game ends.
* The function CalcRewardForGameState calculates the reward which is used for the backpropagation.
*/
void MCTSSimulation(NodeElement& nodeElement) {
	float reward;
	bool simulationTurn = !nodeElement.nodeTurnIndex;

	int* simulationGameState = new int[9]{ 0 };
	for (int i = 0; i < 9; i++) { simulationGameState[i] = nodeElement.currentGameState[i]; }

	while (!HasGameEnded(simulationGameState)) {
		int randNum = (rand() % 9);
		if (simulationGameState[randNum] == 0) {
			if (simulationTurn) { *(simulationGameState + randNum) = 1; simulationTurn = !simulationTurn; }
			else if (!simulationTurn) { *(simulationGameState + randNum) = -1; simulationTurn = !simulationTurn; }
		}
	}
	reward = CalcReward(simulationGameState);
	delete[] simulationGameState;
	MCTSBackpropagation(nodeElement, reward);
}

/*
* Backpropagation
* Starting at the current nodeElement the visitingCount and reward are updated all the way up to the root node, where this function terminates. 
*/
void MCTSBackpropagation(NodeElement& nodeElement, float reward) {
	nodeElement.visitingCount++;
	nodeElement.reward += reward;
	if (!nodeElement.isRootNode) {
		MCTSBackpropagation(*(nodeElement.parentPointer), reward);
	}
}

/*
* Destruction
* Starting at the rootNode, the childNodes are determinatedand the root node deleted.This pattern continuous all the way down to the leaf nodes.
*/
void DestroyMCTSTree(NodeElement* nodeElement) {
	if (nodeElement == NULL) { return; }
	for (int i = 0; i < (*nodeElement).childrenPointer.size(); i++) {
		DestroyMCTSTree(nodeElement->childrenPointer[i]);
	}
	delete nodeElement;
}
#include "Header.h"
#include <cmath>
#include <stdlib.h>
#include <time.h> 

//Non-primitive Data
int* gameStateArray;
NodeElement* currentRootNode;

//Primitive Data
int selectGameMode; //The variable with which the game Mode can be selected
bool termination=false; //Triggers the main game loop if it becomes true the program terminates
GameState gameMode = MainMode; //The switch variable shows in which state the finite state machines currently is inside

//Assistance Data
int totalAmountOfGames = 0;
int totalAmountOfWinsForMCTS = 0;
int totalAmountOfLosesForMCTS = 0;

//Configuration
float c_explorationValue=8; //Degree of exploration the higer it is, the more exploration is going to happen
int c_maxAmountOfGames = 100; //Total amount of whole games that will be played
int c_maxAmountOfMCTSIterations = 1000; //How many iterations the MCTS is allowed to make
bool c_mainTurnIndex = true; //true means the player will start, false means AI will start
bool c_showMainGame = false; //true if the player wants to see the gameplay, false if the player is only interested in the results
bool c_playerMode = false; //true if the player wants to play himself, false if the player wants the ai to play against itself


int main() {
	//Init
	srand(time(NULL));

	//Main game loop
	while (!termination) {
		switch (gameMode){
		case MainMode:
			MainMenu();
			break;
		case AIMode:
			AIMenu();
			break;
		case PlayerMode:
			PlayerMenu();
			break;
		}
	}
	return 0;
}

//Script for Main Menu
void MainMenu() { 
	std::cout << "Select game Mode: 0 = Simulation, 1 = Play, 2 = End Game " << std::endl;
	std::cin >> selectGameMode;
	if (selectGameMode == 0) { 
		std::cout << "Calculations are running, please wait..."<< std::endl;
		c_showMainGame = false;
		c_playerMode = false; 
		gameStateArray = new int[9]{ 0 };
		totalAmountOfGames = 0;
		totalAmountOfWinsForMCTS = 0;
		totalAmountOfLosesForMCTS = 0;
		gameMode = AIMode;
	}
	else if (selectGameMode == 1) { 
		c_showMainGame = true;
		c_playerMode = true;
		gameStateArray = new int[9]{ 0 };
		std::cout << "New Game:" << std::endl;
		PrintGameState(gameStateArray);
		gameMode = PlayerMode;
	}
	else if (selectGameMode == 2) { termination = true; }
}

//Script for AI Menu
void AIMenu() {
	while (c_maxAmountOfGames > totalAmountOfGames) {
		if (c_mainTurnIndex) {
			int randNum = (rand() % 9);
			if (gameStateArray[randNum] == 0) {
				c_mainTurnIndex = !c_mainTurnIndex;
				gameStateArray[randNum] = 1;
				if (c_showMainGame) { std::cout << "Players Turn:" << std::endl; PrintGameState(gameStateArray); }
			}
		}
		else {
			MCTSMode();
		}
		if (HasGameEnded(gameStateArray)) {
			DisplayCurrentResults();
			if (c_maxAmountOfGames > totalAmountOfGames) {
				gameStateArray = new int[9]{ 0 };
				if (c_showMainGame) { std::cout << "New Game:" << std::endl; PrintGameState(gameStateArray); }
			}
			gameMode = MainMode;
		}
	}
	DisplayAllResults();
}

//Script for Player Menu
void PlayerMenu() {
	if (c_mainTurnIndex) {
		int currentIndexChoosen;
		std::cout << "Use numpad to select an action: " << std::endl;
		std::cin >> currentIndexChoosen;
		currentIndexChoosen--; //So PC can more easily use the numpad
		if (gameStateArray[currentIndexChoosen] == 0 && currentIndexChoosen < 9 && currentIndexChoosen >= 0) {
			c_mainTurnIndex = !c_mainTurnIndex;
			gameStateArray[currentIndexChoosen] = 1;
			if (c_showMainGame) { std::cout << "Players Turn:" << std::endl;  PrintGameState(gameStateArray); }
		}
	}
	else {
		MCTSMode();
	}
	if (HasGameEnded(gameStateArray)) {
		DisplayCurrentResults();
		gameMode = MainMode;
	}
}

//This mode makes MCTS calculations
void MCTSMode() {
	currentRootNode = new NodeElement(gameStateArray);
	for (int i = 0; i < c_maxAmountOfMCTSIterations; i++) {
		MCTSSelection(*currentRootNode);
	}
	for (int i = 0; i < 9; i++) { gameStateArray[i] = (*currentRootNode).childrenPointer[FindBestRewardChildIndex(*currentRootNode)]->currentGameState[i]; }
	c_mainTurnIndex = !c_mainTurnIndex;

	if (c_showMainGame) { std::cout << "AIs Turn:" << std::endl; PrintGameState(gameStateArray); }
	DestroyMCTSTree(currentRootNode);
}

//Displays the results of the current game
void DisplayCurrentResults() {
	int finalRewardForDisplay = CalcReward(gameStateArray);
	if (finalRewardForDisplay == 1){ totalAmountOfWinsForMCTS++; }
	if (finalRewardForDisplay == -1){ totalAmountOfLosesForMCTS++; }

	if (c_showMainGame) {
		if (finalRewardForDisplay == 1) { std::cout << "AI Won!" << std::endl; }
		else if (finalRewardForDisplay == 0) { std::cout << "Draw!" << std::endl; }
		else if (finalRewardForDisplay == -1) { std::cout << "Player Won!" << std::endl; }
	}

	totalAmountOfGames++;
	delete[] gameStateArray;
}

//Displays the final combined result of all games that have been made
void DisplayAllResults() {
	std::cout << std::endl;
	std::cout << "Amount of iterations: " << c_maxAmountOfMCTSIterations << std::endl;
	std::cout << "Value of exploration: " << c_explorationValue << std::endl;
	std::cout << "Amount of games: " << totalAmountOfGames << std::endl;
	std::cout << std::endl;
	std::cout << "MCTS wins: " << totalAmountOfWinsForMCTS << std::endl;
	std::cout << "Draw: " << (totalAmountOfGames- totalAmountOfWinsForMCTS- totalAmountOfLosesForMCTS) << std::endl;
	std::cout << "MCTS loses: " << totalAmountOfLosesForMCTS << std::endl;
	std::cout << std::endl;
}
# TicTacToeMCTS
Inspired by the publication "Efficient Selectivity and Backup Operators in Monte-Carlo Tree Search" by Rémi Coulom I wanted to create an AI for the board game TicTacToe which uses the Monte Carlo Tree Search.

There are 2 game modes: 
In Simulation Mode, the AI which is using the MCTS method plays against an AI which makes random choices. In Play Mode, the player can play against the AI, which is using the MCTS method.

## MCTS How it works
The Monte Carlo Tree Search (MCTS) is a method for finding solutions to decision-making problems by using random Simulations as a way to make good predictions.

### Selection
Starting at the top of the tree, the MCTS wants to select the best child Node at each layer. The problem the AI is faced with is called Multi-Armed-Bandit problem. The name derives from the slot machines in a casino. In this problem, a decision maker is faced with the obstacle of finding the most profitable slot machine, without knowing their underlying reward distributions. The following example illustrates how the problem can be tackled.

Imagine going on a holiday for two weeks, where you want to eat out each evening. There are 3 restaurants in your general area. Each day you have to ask yourself: I want to go to the best restaurant, which one is it? An intuitive way of doing that, would be to simply go online and check the reviews. But let's say we can't obtain this information. How do we find out which restaurant is the best? Choosing a random restaurant each day is a possibility. But this isn't very helpful for finding the best restaurant. A better approach would be to visit each restaurant once, and then sticking with the best one for the remainder of the holiday. But this method also has its problems, it might just have happened that at the day we visited the best restaurant, the staff was just having a bad day. Thus, we would give it a bad rating even though it is the best restaurant. So maybe instead of just visiting each restaurant once and then settling with the best one. We could expand the exploration part, so that at every second day we explore and give the restaurant in doubt another chance if we haven't visited it that often. Finding an optimal trade-off between exploring the restaurants and exploiting the currently best one is key. Luckily finding  a good balance between them can be achieved by using the following formula called Upper Bound Confidence For Trees (UCT1): 

<img src="https://latex.codecogs.com/svg.image?\text{UCB1}=\overline{X}_{j}&space;&plus;&space;\sqrt{\frac{2\ln(n)}{n_{j}}}">

The left term of the formula represents the exploiting term, where <img src="https://latex.codecogs.com/svg.image?\overline{X}_{j}"> is the mean reward of the node <img src="https://latex.codecogs.com/svg.image?j">. The right term of the formula represents the exploration term. Where <img src="https://latex.codecogs.com/svg.image?n&space;"> is the amount of times the parent node has been visited. And <img src="https://latex.codecogs.com/svg.image?n_{j}"> represents the amount of times the current node <img src="https://latex.codecogs.com/svg.image?j"> has been visited.

It presents a good trade-off between exploring options which haven't been visited often, and exploiting the current best option. And is the formula I use to find the best Child at each layer.

### Expansion

### Simulation

### Backpropagation

## Future work
- Frontend :    Currently there is no other GUI other then the terminal. Inspired by the work of [vgarciasc](https://github.com/vgarciasc/mcts-viz) I want to                   create a representation that shows how the tree expands. But unlike in vgarciasc work, where the tree can only be expanded by the user stepwise.                 I want to make a representation in which the tree grows kinda like in a time lapse without further input by the user. 
- Optimization: As of right now there is no way of knowing where the nodeElement entities are stored in memory, which means they could be placed far apart. A                   better way would be to store the elements near each other.
- Optimization: There are far too many loopings going on, some reductions could be made here. 
- Optimization: As of right now each nodeElement, stores an array of the currentGameState, this probably shouldn't be necessary.

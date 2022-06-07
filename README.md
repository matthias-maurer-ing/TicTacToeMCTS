# TicTacToeMCTS
## Introduction
Inspired by the publication "Efficient Selectivity and Backup Operators in Monte-Carlo Tree Search" by Rémi Coulom I wanted to create an artificial intelligence (AI) for the board game TicTacToe, which uses the Monte Carlo Tree Search (MCTS).

Currently, there are 2 game modes: 

Play Mode: User vs. AI (MCTS)

<img src="https://user-images.githubusercontent.com/105277072/172359594-08e425ba-c38f-4314-8cdc-d9dd40e9f91b.PNG" width="500">

Simulation Mode: AI (Random decisions) vs. AI (MCTS)

<img src="https://user-images.githubusercontent.com/105277072/172371164-f31c58a1-cb6b-45b3-a6a2-6c5d200e1d1b.PNG" width="500">

## MCTS How it works
The Monte Carlo Tree Search is a method for finding solutions to decision-making problems by using random Simulations as a way to make good predictions. An asymmetrical tree is built around the root node, by repeatedly iterating over the following 4 steps: Selection, expansion, simulation and backpropagation.  

<img src="https://i.stack.imgur.com/DsSXt.png" width="500">
[Source](https://ai.stackexchange.com/questions/23811/how-does-the-mcts-tree-look-like)

### Selection
In the selection phase, the algorithm wants to find the best child Node so that the tree can grow in the most prospering areas.

Imagine going on a vacation for two weeks, where you want to eat out each evening. There are 3 restaurants in your general area. Each day you have to ask yourself: I want to go to the best restaurant, which one is it? An intuitive way of doing that, would be to simply go online and check the reviews. But let's say we can't obtain this information. How do we find out which restaurant is the best? Choosing a random restaurant each day is a possibility. But this isn't very helpful for finding the best restaurant. A better approach would be to visit each restaurant once, and then sticking with the best one for the remainder of the holiday. But this method also has its limitations, it might just have happened that on the day we visited the best restaurant, the staff was just having a bad day. Thus, we would give it a bad rating even though it is the best restaurant. So maybe instead of just visiting each restaurant once and then settling with the best one, we could further increase the exploration part until we have a nice balance between exploration and exploitation. The following formula, called Upper Confidence Bound (UCB1), gives us a good trade-off between them:

<img src="https://latex.codecogs.com/svg.image?\text{UCB1}=\overline{X}_{j}&space;&plus;&space;\sqrt{\frac{2\ln(n)}{n_{j}}}"> 

The left term of the formula represents the exploiting term, where <img src="https://latex.codecogs.com/svg.image?\overline{X}_{j}"> is the mean reward of the node <img src="https://latex.codecogs.com/svg.image?j">. The right term of the formula represents the exploration term. Where  <img src="https://latex.codecogs.com/svg.image?n&space;"> is the amount of times the parent node has been visited. And <img src="https://latex.codecogs.com/svg.image?n_{j}"> represents the amount of times the current node <img src="https://latex.codecogs.com/svg.image?j"> has been visited.

It presents a good trade-off between exploring options which haven't been visited often, and exploiting the current best option. It is the formula I use to find the best child at each layer.


### Expansion
After the Selection phase has reached a leaf node, the expansion phase begins. In which a random action from the pool of possible actions left is selected. A new node element with a  new game state is created.

### Simulation
In the simulation phase the newly created game state will be used as a starting point for a random simulation. Here, each side takes random actions until the game terminates. Depending on which side is winning the reward can be positve or negative. 

But how can random simulations lead up to something useful? This will be discussed here soon. //TO-DO

### Backpropagation
In the end, the reward of the simulation is getting backpropagated to the root node. Every node visited updates its visiting counter and respective reward values.

## Future work

- Frontend :    Currently there is no other GUI other than the terminal. Inspired by the work of [vgarciasc](https://github.com/vgarciasc/mcts-viz) I want to create a visualization that shows how the tree expands. But unlike in vgarciasc work, where the tree can only be expanded by the user stepwise.  I want to make a representation in which the tree grows kinda like in a time-lapse without further input by the user. 
- Optimization: As of right now, there is no way of knowing where the node Element entities are stored in memory, which means they could be placed far apart. A better way would be to store the elements near each other.
- Optimization: There are far too many loops going on, some reductions could be made here. 
- Optimization: As of right now each node Element, stores an array of the currentGameState, this probably shouldn't be necessary.

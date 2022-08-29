# TicTacToeMCTS
## Introduction
Inspired by the publication "Efficient Selectivity and Backup Operators in Monte-Carlo Tree Search" by Rémi Coulom I wanted to create an artificial intelligence (AI) for the board game TicTacToe, which uses the Monte Carlo Tree Search (MCTS), in order to improve my C++ knowledge.

Currently, there are 2 game modes: 

Play Mode: Here the User plays against the AI (MCTS).

<img src="https://user-images.githubusercontent.com/105277072/172359594-08e425ba-c38f-4314-8cdc-d9dd40e9f91b.PNG" width="500">

Simulation Mode: Here the AI (MCTS) plays against an AI (Random) which makes random decisions.

<img src="https://user-images.githubusercontent.com/105277072/172371164-f31c58a1-cb6b-45b3-a6a2-6c5d200e1d1b.PNG" width="500">

## MCTS How it works
The Monte Carlo Tree Search is a method for finding solutions to decision-making problems by using random Simulations as a way to make good predictions. An asymmetrical tree is built around the root node, by repeatedly iterating over the following 4 steps: Selection, expansion, simulation and backpropagation.  

<img src="https://i.stack.imgur.com/DsSXt.png" width="500">

[Image source](https://i.stack.imgur.com/DsSXt.png)

### Selection
In the selection phase, the algorithm wants to find the best child Node so that the tree can grow in the most prospering areas.

In order to manage this, the AI has to first try out some areas. An intuitive way of solving this problem would be to make the AI stick to the first areas that yields high rewards. But this would take us only so far, as there might be better areas to seek, but that way the AI would only stick to the first area which yields some reward. By introducing a metric for exploration, we can give areas a chance to be explored. If an area hasn't been visited often, the AI will be more interested to look into it. In order to gain best results, it is of interest for us to find a nice balance between exploration and exploitation, as too much exploration would be obviously leading us no where.

So we can use the following formula, called Upper Confidence Bound (UCB1), which gives us a good trade-off between exploration and exploitation:

<img src="https://latex.codecogs.com/svg.image?\bg{white}\text{UCB1}=\overline{X}_{j}&space;&plus;&space;\sqrt{\frac{2\ln(n)}{n_{j}}}"> 

The left term of the formula represents the exploiting term, where <img src="https://latex.codecogs.com/svg.image?\overline{X}_{j}"> is the mean reward of the node <img src="https://latex.codecogs.com/svg.image?\bg{white}j">. The right term of the formula represents the exploration term. Where  <img src="https://latex.codecogs.com/svg.image?\bg{white}n&space;"> is the amount of times the parent node has been visited. And <img src="https://latex.codecogs.com/svg.image?\bg{white}n_{j}"> represents the amount of times the current node <img src="https://latex.codecogs.com/svg.image?\bg{white}j"> has been visited.

It presents a good trade-off between exploring options which haven't been visited often, and exploiting the current best option. It is the formula I use to find the best child at each layer.


### Expansion
After the Selection phase has reached a leaf node, the expansion phase begins. In which a random left action from the pool of possible actions is selected. A new node element with a new game state is created.

### Simulation
In the simulation phase the newly created game state will be used as a starting point for the random simulation. Here, each side makes random decisions until the game terminates. Depending on which side is winning the reward will either be positve or negative. 


### Backpropagation
In the end, the reward of the simulation is getting backpropagated to the root node. Every node which has been visited updates its visiting counter and respective reward values.

## Future work

- Frontend :    Currently there is no other GUI other than the terminal. Inspired by the work of [vgarciasc](https://github.com/vgarciasc/mcts-viz) I want to create a visualization that shows how the tree expands. But unlike in vgarciasc work, where the tree can only be expanded by the user stepwise.  I want to make a representation in which the tree grows kinda like in a time-lapse without further input by the user. 
- Optimization: As of right now, there is no way of knowing where the node Element entities are stored in memory, which means they could be placed far apart. A better way would be to store the elements near each other.

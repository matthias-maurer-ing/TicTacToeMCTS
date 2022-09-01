# TicTacToeMCTS
## Introduction
Inspired by the publication "Efficient Selectivity and Backup Operators in Monte-Carlo Tree Search" by Rémi Coulom I wanted to create an artificial intelligence (AI) for the board game TicTacToe, which uses the Monte Carlo Tree Search (MCTS).

Currently, there are 2 game modes: 

Play Mode: Here the User plays against the AI (MCTS).

<img src="https://user-images.githubusercontent.com/105277072/172359594-08e425ba-c38f-4314-8cdc-d9dd40e9f91b.PNG" width="600">

Simulation Mode: Here the AI (MCTS) plays against an AI (Random) which makes random decisions.

<img src="https://user-images.githubusercontent.com/105277072/172371164-f31c58a1-cb6b-45b3-a6a2-6c5d200e1d1b.PNG" width="600">

## MCTS How it works
The Monte Carlo Tree Search is a method for finding solutions to decision-making problems by using random Simulations as a way to make good predictions. An asymmetrical tree is built around the current turn, by repeatedly iterating over these 4 steps: Selection, expansion, simulation and backpropagation.  

<img src="https://i.stack.imgur.com/DsSXt.png" width="500">

[Image source](https://i.stack.imgur.com/DsSXt.png)

### Selection
Starting at the root node, the algorithm wants to find the best child Node so that the tree can grow in the most prospering areas.

An intuitive way of solving this problem would be to make the AI stick to the first general area which yields high rewards. But this would take us only so far, as there might be better areas hiding which the AI doesn't consider anymore, as it sticks to the first good general area. This problem can be circumvented by introducing an exploration metric. This way, we can tell the AI as to how much exploration should be happening, so that the AI doesn't strictly stick to the first good area it finds. That means that areas that haven't been visited often, will gain a reward bonus through the exploration metric. But we don't want this bonus to become too large, as this would mean that the AI would constantly seek out areas that haven't been visited often. So, finding a good balance between exploration and exploitation is key.

This trade of can be reached by using the following formula, called Upper Confidence Bound (UCB1), which gives us a good trade-off between exploration and exploitation:

<img src="https://latex.codecogs.com/svg.image?\bg{white}\text{UCB1}=\overline{X}_{j}&space;&plus;&space;\sqrt{\frac{2\ln(n)}{n_{j}}}"> 

The left term of the formula represents the exploiting term, where <img src="https://latex.codecogs.com/svg.image?\overline{X}_{j}"> is the mean reward of the node <img src="https://latex.codecogs.com/svg.image?\bg{white}j">. The right term of the formula represents the exploration term. Where  <img src="https://latex.codecogs.com/svg.image?\bg{white}n&space;"> is the amount of times the parent node has been visited. And <img src="https://latex.codecogs.com/svg.image?\bg{white}n_{j}"> represents the amount of times the current node <img src="https://latex.codecogs.com/svg.image?\bg{white}j"> has been visited.

It presents a good trade-off between exploring options which haven't been visited often, and exploiting the current best option. It is the formula I use to find the best child at each layer.


### Expansion
After the Selection phase has reached a leaf node, the expansion phase begins. In which a random left action from the pool of possible actions is selected. A new node element with a new game state is created.

### Simulation
In the simulation phase the newly created game state will be used as a starting point for the random simulation. Here, each side makes random decisions until the game terminates. Depending on which side is winning the reward will either be positve or negative. 


### Backpropagation!

In the end, the reward of the simulation is getting backpropagated to the root node. Every node which has been visited updates its visiting counter and respective reward values.

## Results

<img src="https://user-images.githubusercontent.com/105277072/187986721-42ea5594-ae6a-4148-bb20-be0838e0b8e0.PNG" width="600">

As one can clearly see here, the AI which was build using the MCTS clearly outperforms the AI which simply makes random decisions. This can also be observed when playing the game, as the AI clearly anticipates when the User tries to outmaneuver it. With a common win rate at around 90%+ for the MCTS AI, I consider this a successful project. 

## Future work

- Frontend :    Currently there is no other GUI other than the terminal. Inspired by the work of [vgarciasc](https://github.com/vgarciasc/mcts-viz) I want to create a visualization that shows how the tree expands. But unlike in vgarciasc work, where the tree can only be expanded by the user stepwise.  I want to make a representation in which the tree grows kinda like in a time-lapse without further input by the user. 
- Optimization: As of right now, there is no way of knowing where the node Element entities are stored in memory, which means they could be placed far apart. A better way would be to store the elements near each other.

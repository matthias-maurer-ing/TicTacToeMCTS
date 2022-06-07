# TicTacToeMCTS
## Introduction
Inspired by the publication "Efficient Selectivity and Backup Operators in Monte-Carlo Tree Search" by Rémi Coulom I wanted to create an artificial intelligence (AI) for the board game TicTacToe, which uses the Monte Carlo Tree Search (MCTS).

Currently, there are 2 game modes: 
Play Mode: User vs. AI (MCTS)
Simulation Mode: AI (Random Decisions) vs. AI (MCTS)

## MCTS How it works
The Monte Carlo Tree Search is a method for finding solutions to decision-making problems by using random Simulations as a way to make good predictions. An asymetrical tree is build around the current turn, by repeadetly iterating over the following 4 steps: Selection, expansion, simulation and backpopagation.  

### Selection
Starting at the current game state, the MCTS wants to select the best child node to follow out of all possible actions that can be taken at the current game state. This dillema the AI is faced with is called Multi-Armed-Bandit problem. The name derives from the slot machines in a casino. In this problem, a decision maker is faced with the obstacle of finding the most profitable slot machine, without knowing their underlying reward distributions. The following example illustrates how the problem can be tackled.
Imagine going on a holiday for two weeks, where you want to eat out each evening. There are 3 restaurants in your general area. Each day you have to ask yourself: I want to go to the best restaurant, which one is it? An intuitive way of doing that, would be to simply go online and check the reviews. But let's say we can't obtain this information. How do we find out which restaurant is the best? Choosing a random restaurant each day is a possibility. But this isn't very helpful for finding the best restaurant. A better approach would be to visit each restaurant once, and then sticking with the best one for the remainder of the holiday. But this method also has its problems, it might just have happened that at the day we visited the best restaurant, the staff was just having a bad day. Thus, we would give it a bad rating even though it is the best restaurant. So maybe instead of just visiting each restaurant once and then settling with the best one. We could expand the exploration part, so that at every fourth day we explore and give the restaurant in doubt another chance if we haven't visited it that often. This can be further improved by increasing the amount of exploration, but not to much as always exploring leads to the selecting randomly sceneraio. So finding an optimal trade-off between exploring the restaurants and exploiting the currently best one is key. Luckily finding a good balance between them can be achieved by using the following formula called Upper Confidence Bound (UCB1): 
<img src="https://latex.codecogs.com/svg.image?\text{UCB1}=\overline{X}_{j}&space;&plus;&space;\sqrt{\frac{2\ln(n)}{n_{j}}}">
The left term of the formula represents the exploiting term, where <img src="https://latex.codecogs.com/svg.image?\overline{X}_{j}"> is the mean reward of the node <img src="https://latex.codecogs.com/svg.image?j">. The right term of the formula represents the exploration term. Where <img src="https://latex.codecogs.com/svg.image?n&space;"> is the amount of times the parent node has been visited. And <img src="https://latex.codecogs.com/svg.image?n_{j}"> represents the amount of times the current node <img src="https://latex.codecogs.com/svg.image?j"> has been visited.

It presents a good trade-off between exploring options which haven't been visited often, and exploiting the current best option. It is the formula I use to find the best Child at each layer.

### Expansion
After the Selection phase has reached a leaf node the expansion phase begins. In which a random action from the pool of possible actions left is selected. A new node element with a  new game state is created.
### Simulation
In the simulation phase the newly created game state will be used as a starting point for a random simulation. Here, each side takes random actions until the game terminates. Depending on which side is winning the reward can be positve or negative. 

#### How can random simulations lead to anything useful?  

Given the following function: <img src="https://latex.codecogs.com/svg.image?f(x)=x^2"> in this interval: <img src="https://latex.codecogs.com/svg.image?x\in&space;[0,1]"><img src="blob:https://www.desmos.com/2750c721-3d64-4213-85a5-a47c2bef870d">

How do you go about estimating the are beneath the function non analyticaly?
Random simulations!


So how can these random simulation contribute to make better predictions? Well in order for this algorithm to work a lot of iterations are being made. Which means, when the tree starts to grow in prospering areas, the likeliyhood of such random random contributing to a broader perception increases. A good example for this would be the average geight of a human. If would meassure the height of a handfull of people this would not represent the average height of a human accuratley. But if we increase the amount of people we massure we get a good estimation for the average height of a human, without having to meassure each person indivitudally.

### Backpropagation
In the end the reward of the simulation is getting backpropagated to the root node. Every node visitied updates its visiting counter and respective reward values.

## The Reasons
Inspired by sorting algorithm visualization.
Why do we need that? Well MCTS can return satisfying results wv only a handfull of searching. The intiutive way would be starting at the current Node to expand the whole tree and then using this information, to make the best decision., The MCTS methods works another way, by only doing 100 expansions. The MCTS only dives a little further down into the tree, and still can make pretty good predictions. The only way of doing this would be to smpüly remove the annectode to other user inputs. The application of MCTS to the artificial intelligence is of upper most importance.

## Future work
- Frontend :    Currently there is no other GUI other then the terminal. Inspired by the work of [vgarciasc](https://github.com/vgarciasc/mcts-viz) I want to create a visualization that shows how the tree expands. But unlike in vgarciasc work, where the tree can only be expanded by the user stepwise.  I want to make a representation in which the tree grows kinda like in a time lapse without further input by the user. 
- Optimization: As of right now there is no way of knowing where the nodeElement entities are stored in memory, which means they could be placed far apart. A better way would be to store the elements near each other.
- Optimization: There are far too many loopings going on, some reductions could be made here. 
- Optimization: As of right now each nodeElement, stores an array of the currentGameState, this probably shouldn't be necessary.

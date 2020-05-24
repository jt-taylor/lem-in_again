# lem-in_again
# 42 LemIn

Lem-In is a project tangently related to graph theory and pathfinding alg. ,
The project is different in a few small ways that change the core of what the alg is trying to do .
Those being that we are trying to minimize the number of turns that it takes to move all of the ants from the
starting room to the end room .
* Ants can only move one room per turn
* Only one ant may occupy each room , with the exception of the start and end room
* The program may not take more than 15 seconds to complete
* The program must at least match the number of turns estimated by the generator
* The program must echo the input and the solution to stdout
* The project must be written in c and has a very limited set of allowed functions , see the project pdf for more info


## Getting Started
* Make
* use the generator to create the map or write your own
* feed the input map into the compiled program
* ./generator [option] > ./lem_in > solution

### Prerequisites

Make
C compiler

## Built With
* Make

# Relevant notes on the project
* This project is not about finding the maximum flow between the nodes of the graph , it's about minimizing the turns that it will take to move the ants between them .
* a node in the graph is only ever going to be superimposed on two paths at once
* this solution gets the graph from the layout and then we use a n-ary tree to find the shortest path, and then we find ~15 paths and split them on the intersection nodes .
* there is usually 20 ~ 30 paths in the maximum flow of the graph but the last few paths may take hundreds of turns as opposed to  < 10 nodes seperation
* this is not an implementation of ford-fulkerson or other max-flow alg's
## Acknowledgments

* The generator file was supplied by 42

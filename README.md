# Maze Project

The way that I have implemented the project is with a DFS algorithm using an adjacency list. The boost libraries were not used in the implementation of the project. A makefile is included so the code can be compiled that way. If the makefile does not work the code can be compiled and run with the command below. Once the executable is created the program can be run with the command `./maze`.

All instructions for the project are given in the intructions .txt file provided. 

Example inputs are under the examples folder, these must be in the same directory as the executable and renamed as input.txt to work as intended. The solutions to these examples are also provided in the examples folder.

### Compile and Run Commands

Without makefile
```
g++ -std=c++11 -o maze maze.cpp
./maze
```

With makefile
```
./maze
```

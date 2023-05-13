//The includes used for the project
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <map>

bool DFS_Search(int start, int end, std::map<int, std::vector<int>> &maze, std::map<int, bool> &visitedNodes, std::vector<int> &traversal)
{
    //DFS Algorithm

    //The current node is marked as visited
    visitedNodes[start] = true;
    
    //The current node is pushed back into the traversal vector
    traversal.push_back(start);

    //If the end node is reached finish the algorithm
    if(start == end)
        return true;

    //For all of the neighbors of the current node perform DFS on the ones that have not already been visited
    for (int x : maze[start])
    {
        if(visitedNodes[x] == false)
        {
            if(DFS_Search(x, end, maze, visitedNodes, traversal))
                return true;
        }
    }

    //Remove the last node because the current path did not reach the end node
    traversal.pop_back();

    return false;
}

int main ()
{
    //Reading of the input file and creating the output file to read them
    std::ifstream myfile;
    myfile.open("input.txt");
    std::ofstream output("output.txt");

    //Input verification to make sure the file is not empty
    if (myfile.peek() == std::ifstream::traits_type::eof())
        return 0;

    //Initialization of variables to be used
    int level, row, column, startX, startY, startZ, endX, endY, endZ, startPoint, endPoint;
    std::string text;

    //Gets the Levels of the graph
    getline(myfile, text, ' ');
    level = std::stoi(text);

    //Gets the rows of the graph
    getline(myfile, text, ' ');
    row = std::stoi(text);

    //Gets the columns of the graph
    getline(myfile, text);
    column = std::stoi(text);

    //std::cout << "Levels: " << level << "\nRows: " << row << "\nColumns: " << column << std::endl;

    //Gets the starting\entrance coordinates and puts them in respective variables
    getline(myfile, text, ' ');
    startZ = std::stoi(text);
    startZ *= 100;

    getline(myfile, text, ' ');
    startX = std::stoi(text);
    startX *= 10;

    getline(myfile, text);
    startY = std::stoi(text);

    //Creates a coordinate value for the starting point
    //The coordinates are represented as the 100ths place being the Z (level), 10s place being the Y (row), and 1s place being the X (column)
    startPoint = startZ + startX + startY;
    
    //std::cout << std::setw(3) << std::setfill('0') <<  startPoint << std::endl;

    //Gets the ending\goal coordinates and puts them in respective variables
    getline(myfile, text, ' ');
    endZ = std::stoi(text);
    endZ *= 100;

    getline(myfile, text, ' ');
    endX = std::stoi(text);
    endX *= 10;

    getline(myfile, text);
    endY = std::stoi(text);

    //Creates a coordinate value for the ending point
    endPoint = endZ + endX + endY;
    
    //std::cout << std::setw(3) << std::setfill('0') << endPoint << std::endl;

    /* Graph Initialization */
    //Two maps are used one for the neighbors of the nodes and one for if the nodes have been visited yet
    std::map<int, std::vector<int>> maze;
    std::map<int, bool> visitedNodes;

    /* This is for Getting Neighbors */
    //Read character by character from the file, if a space is encountered curCol++; if '\n' encountered curCol = 0 && curRow++; if curRow == row --> curRow = 0 && curLevel++
    //curCount reset every space
    char curChar;
    int curCol = 0, curRow = 0, curLevel = 0, curCount = 0, curPos = 0;
    //curPos will have a range from 0 to 5

    //The curPoint and nPoint are the current point and the neighbor of the new point
    int curPoint = 0, nPoint = 0;

    //Reads character by character of each cell to see if that cell can go in any direction
    while (myfile.get(curChar))
    {
        //Creates a coordinate for the current position
        curPoint = curLevel*100 + curRow*10 + curCol;

        //If the current char is 1 then the current cell can traverse to a neighbor cell
        if(curChar == '1')
        {
	    //The curPos is the current position of the 6 byte binary character and will tell the program if the current node can go North, East, South, West, up, or Down
            switch (curPos)
            {
                case 0:
        	  	    nPoint = curPoint - 10;             //If the current node can go north then the neighbor point is one row above (-10) from the current node 
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm 
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                case 1:
                    nPoint = curPoint + 1;              //If the current node can go east then the neighbor point is one column to the rigth (+1) from the current node 
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                case 2:
                    nPoint = curPoint + 10;             //If the current node can go south then the neighbor point is one row below (+10) from the current node
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                case 3:
                    nPoint = curPoint - 1;              //If the current node can go west then the neighbor point is one column to the left (-1) from the current node
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                case 4:
                    nPoint = curPoint + 100;            //If the current node can go up then the neighbor point is one level above (+100) from the current node
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                case 5:
                    nPoint = curPoint - 100;            //If the current node can go down then the neighbor point is one level below (-100) from the current node
                    visitedNodes[curPoint] = false;     //The node is initialized to have not being visited by the DFS algorithm
                    maze[curPoint].push_back(nPoint);   //The neighbor node is pushed back into the current node's adjacency list
                    break;
                default:
                    break;
            }
        }

        //If the 6 bit character is finished then the current nodes neighbors have been recorded and it is time to go to the next node
        if(curChar == ' ')
        {
            //Position is reset and the current column is increased by 1
            curPos = 0;
            curCol++;
            continue;
        }

        //If the line is finished then the row needs to be increased and the column and position need to be reset
        if(curChar == '\n')
        {
            //The current column and position is reset while the row is increased.
            curCol = 0;
            curRow++;
            curPos = 0;

            //If the current row is equal to the number of rows the maze has then reset the row and add one to the level
            if(curRow == row)
            {
                curRow = 0;
                curLevel++;
            }
            continue;
        }
        //The current position is increased per iteration
        curPos++;
    }

    //Traversal vector for the path that is traversed in the DFS Algorithm from the starting point to the end point
    std::vector<int> traversal;

    //DFS Search
    DFS_Search(startPoint, endPoint, maze, visitedNodes, traversal);

    //Used for printing out the traversal vector
    //for(int i = 0; i < traversal.size() - 1; i++)
    //    std::cout << (traversal[i] - traversal[i-1]) << std::endl;

    //This is the calculations done to figure out the method of traversal from the DFS Search using the traversal vector     
    for(int i = 0; i < traversal.size() - 1; i++)
    {
        //The temp int will always be 1, -1, 10, -10, 100, or -100 because of the coordinate system used
        //The temp int will hold the path in a numerical value traveled from the current node to the next node
        int temp = traversal[i] - traversal[i+1];

        //Switch statement to convert the numerical representation to a string/character representaion
        switch(temp)
        {
            //Depending on the numerical value calculated the switch statement will add the corresponding character to the output file
            case -1:
                //The curent node went east
                output << "E";
                break;
            case 1:
                //The curent node went west
                output << "W";
                break;
            case -10:
                //The curent node went south
                output << "S";
                break;
            case 10:
                //The curent node went north
                output << "N";
                break;
            case -100:
                //The curent node went up
                output << "U";
                break;
            case 100:
                //The curent node went down
                output << "D";
                break;
            default:
                break;
        }
        //Adds a space to the output file inbetween characters unless it is the end of the calculations
        if(i != traversal.size() - 2)
            output << " ";
    }
    
    /* This is for printing the adjacency list
    for(const auto& pair : maze)
    {
        std::cout << "key: " << pair.first << "\tvalue: ";
        for(int itr : pair.second)
            std::cout << itr << " ";
        std::cout << "\n" << std::endl;
    }
    */

    //Close the files and end the program
    myfile.close();
    output.close();
    return 0;
}

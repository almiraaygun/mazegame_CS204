#include <iostream>
#include <fstream>
#include <string>

#include "maze.h"

using namespace std;




Maze::Maze() {
    head = nullptr;
    start = nullptr;
    exit = nullptr;
    player = nullptr;
    score = 0;
    rows = 0;
    cols = 0;
}

void Maze::loadMaze(ifstream& input) {


    string line;
    MazeNode *prevRowHead = nullptr;  // Head of the previous row
    MazeNode *rowHead = nullptr;      // Head of the current row


    while (getline(input, line)) {
        MazeNode *prev = nullptr;
        for (int i = 0; i < line.size(); i++) {
            MazeNode *node = new MazeNode(line[i]);
            if (line[i] == 'X') {
                player = node;
            }
            if (line[i] == 'E') {
                exit = node;
            }

            if (i == 0) {
                if (head == nullptr) {
                    head = node; // Set the head of the maze
                }
                rowHead = node; // Set the head of the current row
            }
            else {
                // Link the previous node in the row to the current node
                prev->right = node;
                node->left = prev;
            }

            // Link the node above to the current node
            if (prevRowHead != nullptr) {
                MazeNode *aboveNode = prevRowHead;
                for (int j = 0; j < i; j++) {
                    aboveNode = aboveNode->right;
                }
                aboveNode->down = node;
                node->up = aboveNode;
            }

            prev = node; // Move to the next node in the row
        }
        prevRowHead = rowHead; // Move to the next row
    }

    input.close();
    cout << "Maze loaded. Start exploring!" << endl;
}

void Maze::printMaze() {
    if(head != nullptr){
        MazeNode * tempDown = head;
        while(tempDown != nullptr){
            MazeNode * tempRight = tempDown;
            while(tempRight != nullptr){
                cout << tempRight->cellContent << " ";
                tempRight = tempRight->right;
            }
            tempDown = tempDown->down;
            cout << endl;
        }
    }
    else
    {
        cout << "Maze is not loaded, so empty." << endl;
    }
}



bool Maze::canMove(char direction)const {
    //direction can be up,down,right,left

    if (direction == 'R') {
        if (player->right == nullptr) {
            cout << "Cannot move: Out of the maze bound." << endl;
            return false;
        } else if (player->right->cellContent == '#') {
            cout << "Cannot move: There is a wall in that direction." << endl;
            return false;
        } else {
            return true;
        }
    }

    else if (direction == 'L') {
        if (player->left == nullptr) {
            cout << "Cannot move: Out of the maze bound." << endl;
            return false;
        } else if (player->left->cellContent == '#') {
            cout << "Cannot move: There is a wall in that direction." << endl;
            return false;
        } else {
            return true;
        }
    }

    else if (direction == 'U') {
        if (player->up == nullptr) {
            cout << "Cannot move: Out of the maze bound." << endl;
            return false;
        } else if (player->up->cellContent == '#') {
            cout << "Cannot move: There is a wall in that direction." << endl;
            return false;
        } else {
            return true;
        }
    }

    else {
        if (player->down == nullptr) {
            cout << "Cannot move: Out of the maze bound." << endl;
            return false;
        } else if (player->down->cellContent == '#') {
            cout << "Cannot move: There is a wall in that direction." << endl;
            return false;
        } else {
            return true;
        }
    }
}

void Maze::move(char direction) {
    if (canMove(direction)) {
        player->cellContent = '.';
        if (direction == 'R') {
            player = player->right;
        } else if (direction == 'L') {
            player = player->left;
        } else if (direction == 'U') {
            player = player->up;
        } else if (direction == 'D') {
            player = player->down;
        }

        if (player->cellContent == 'I') {
            cout << "You found an item worth 204 points!" << endl;
        }
        player->cellContent = 'X';
    }
}

void Maze::collectItem() {
    if (player->cellContent=='I'){
        score=score+204;
        cout<<"Item collected! Your score is now "<< score <<endl;
        player->cellContent= '.';
    }
    else
        cout<<"No item to collect here."<<endl;
}


void Maze::EndtheGame() {
    cout<<"Game ended by the player."<<endl;
    cout<<"Final score: "<< score<<endl;

}
void Maze::Exit() {
    cout<< "Congratulations! You reached the exit!"<<endl;
    cout<< "Final score: "<< score<<endl;

}

Maze::~Maze() {
    // Iterate through the 2D linked list and delete each node
    MazeNode*currentRow=head;
    while(currentRow!=nullptr){
        MazeNode*currentCol=currentRow;
        currentRow=currentRow->down;
        while(currentCol!=nullptr){
            MazeNode*temp=currentCol;
            currentCol=currentCol->right;
            delete temp;
        }
    }
}

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct MazeNode {
    char cellContent;
    MazeNode* right;
    MazeNode* left;
    MazeNode* up;
    MazeNode* down;

    MazeNode(char content) : cellContent(content), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {}
};

class Maze {
private:
    MazeNode * head;
    MazeNode* start;
    MazeNode* exit;
    MazeNode* player;
    int score;
    int rows;
    int cols;



public:
    Maze();
    ~Maze();
    void loadMaze(ifstream&);
    void printMaze();
    void move(char direction);
    bool canMove(char direction) const;
    void collectItem();
    void EndtheGame();
    void Exit();
    MazeNode *getPlayer(){
        return player;
    }
    int getScore() const {
        return score;
    }


};

#endif // MAZE_H

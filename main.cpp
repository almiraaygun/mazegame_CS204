#include <iostream>
#include "maze.h"
using namespace std;

int main() {
    Maze maze;
    string filename;
    char direction;
    int score=0;
    bool playing =true;

    cout << "Enter the maze file name: "<<endl;
    cin >> filename;

    ifstream input(filename);
    if (input.fail()) {
        cout << "Unable to open file." << endl;
        cout << "Failed to load maze. Exiting..." << endl;
        return 0;
    }
    maze.loadMaze(input);
    //cout << maze.getPlayer()->cellContent;
    //cout << maze.getPlayer()->left->cellContent;
    //cin.get();

    while(playing){
        cout<<"Enter input (R/L/U/D/P/C/Q):"<<endl;
        cin >> direction;

        if(maze.getPlayer() -> cellContent=='E'){
            maze.Exit();
            playing = false;
            return 0;
        }
        else if (direction=='P'){
            maze.printMaze();
            cout<< "Current score: "<<maze.getScore()<<endl;
        }
        else if(direction=='R'||direction=='L'||direction=='U'||direction=='D'){
            maze.move(direction);
        }
        else if(direction=='C'){
            maze.collectItem();
        }

        else if(direction=='Q'){
            maze.EndtheGame();
            playing = false;
        }
        else{
            cout<<"Invalid input. Please try again."<<endl;
        }
    }
    return 0;
}
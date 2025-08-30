#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void DeAlocationMaze(char**& maze, int row, int i = 0) {
    if (i >= row) {  // Correct base case
        delete[] maze;
        maze = nullptr;
        return;
    }
    delete[] maze[i];
    DeAlocationMaze(maze, row, i + 1);
}

bool MazeSolution(char** maze, int size, int i = 0, int j = 0) {
    if (i < 0 || i == size || j < 0 || j == size) return false;
    if (maze[i][j] == '0' || maze[i][j] == '0') return false;
    if (maze[i][j] == 'E') return true;
    if (maze[i][j] != 'S') maze[i][j] = '0';
    
    if (MazeSolution(maze, size, i+1, j)) {
        if (maze[i][j] != 'S')maze[i][j] = 'P'; 
            return true;
        }
    
    if (MazeSolution(maze, size, i-1, j)) {
        if (maze[i][j] != 'S')maze[i][j] = 'P';
           return true;
        }
        
    if (MazeSolution(maze, size, i, j + 1)) {
        if (maze[i][j] != 'S')maze[i][j] = 'P';
           return true;
        }
    
    if (MazeSolution(maze, size, i, j - 1)) {
        if (maze[i][j] != 'S')maze[i][j] = 'P';
           return true;
        }
    
    return false;
}

void displayMaze(char**& maze, int row, int col, int i = 0, int j = 0) {
    if (i == row) {   
        cout << endl;
        return;
    }    
    if (j == col) {
        cout << endl;
        return displayMaze(maze, row, col, i + 1, 0);
    }
    cout << maze[i][j] << " ";
    return displayMaze(maze, row, col, i, j + 1);
}

void initializeMaze(char**& maze, int row, int col, int i = 0, int j = 0) {
    if (i == row) return;
    if (j == col)
     {
        return initializeMaze(maze, row, col, i + 1, 0);
    }
    if (i == 0 && j == 0) maze[i][j] = 'S';
    else if (i == row - 1 && j == col - 1) maze[i][j] = 'E';
    else maze[i][j] = (rand() % 10 < 3) ? '0' : '1';
    return initializeMaze(maze, row, col, i, j + 1);
}

char** AllocateMaze(char**& maze, int row, int col, int i = 0) {
    if (i == row) 
     {
        return maze;
     }    
    if (i == 0) 
    {
        maze = new char*[row];
    }
    maze[i] = new char[col];
    return AllocateMaze(maze, row, col, i + 1);
}

int main() {
    srand(time(0));
    char** maze = nullptr;
    int size;
    cout << "Enter maze size (maximum=20) : ";
    cin >> size;
    if (size <= 0 || size > 20) {
        cout << "The size is invalid\n";
        return 1;
    }
    
    maze = AllocateMaze(maze, size, size);
    initializeMaze(maze, size, size);
    cout << "Generated MAZE : \n";
    displayMaze(maze, size, size);
    
    bool isP = MazeSolution(maze, size);
    if (isP) {
        cout << "Solved MAZE : \n";
        displayMaze(maze, size, size); 
    } else {
        cout << "No Escape\n";
    }
    DeAlocationMaze(maze, size);
    return 0;
}

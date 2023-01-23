#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stack>
#include <queue>

// Struct to represent a point in the maze
struct Point {
    int x;
    int y;
};

// Class for generating and solving a maze
class Maze {
public:
    // Constructor to initialize the maze with given dimensions
    Maze(int width, int height) : width(width), height(height) {
        // Initialize the maze with walls
        for (int i = 0; i < height; i++) {
            std::vector<int> row;
            for (int j = 0; j < width; j++) {
                row.push_back(1);
            }
            maze.push_back(row);
        }

        // Seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Generate a random maze
        std::vector<Point> stack;
        Point start = {0, 0};
        stack.push_back(start);
        maze[start.y][start.x] = 0;
        while (!stack.empty()) {
            Point current = stack.back();
            std::vector<Point> neighbors = getValidNeighbors(current);
            if (!neighbors.empty()) {
                std::shuffle(neighbors.begin(), neighbors.end(), gen);
                Point next = neighbors[0];
                stack.push_back(next);
                maze[next.y][next.x] = 0;
                removeWall(current, next);
            } else {
                stack.pop_back();
            }
        }
    }

    // Function to solve the maze using a specified algorithm
    void solve(std::string algorithm) {
        if (algorithm == "DFS") {
            solveDFS();
        } else if (algorithm == "BFS") {
            solveBFS();
        } else {
            std::cout << "Invalid algorithm" << std::endl;
        }
    }

    // Function to display the maze
    void display() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze[i][

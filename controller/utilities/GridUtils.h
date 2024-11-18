#ifndef GRIDUTILS_H
#define GRIDUTILS_H

#include <vector>

class GridUtils
{
public:
    // Function to initialize a grid of given size
    static std::vector<std::vector<int>> initializeGrid(int rows, int cols);

    // Function to find the shortest path using a simple algorithm (e.g., BFS)
    static bool findPath(std::vector<std::vector<int>> &grid, int startX, int startY, int endX, int endY);

    // Function to print the grid (for debugging)
    static void printGrid(const std::vector<std::vector<int>> &grid);
};

#endif // GRIDUTILS_H

#include "GridUtils.h"
#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> GridUtils::initializeGrid(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0)); // 0 means empty space
}

bool GridUtils::findPath(std::vector<std::vector<int>> &grid, int startX, int startY, int endX, int endY)
{
    // Simple BFS to find a path
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Directions: up, down, left, right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // If we reach the destination, return true
        if (x == endX && y == endY)
        {
            return true;
        }

        // Explore neighbors
        for (auto &dir : directions)
        {
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && !visited[nx][ny] && grid[nx][ny] == 0)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return false; // No path found
}

void GridUtils::printGrid(const std::vector<std::vector<int>> &grid)
{
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

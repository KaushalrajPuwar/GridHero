#include <iostream>
#include "Position.h"
#include <queue>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

const int GRID_SIZE = 10;

class GridUtils
{
public:
    static vector<Position> findPath(Position start, Position end, vector<vector<int>> &grid)
    {
        vector<Position> path;
        queue<Position> q;
        unordered_set<Position> visited;
        vector<vector<Position>> parent(GRID_SIZE, vector<Position>(GRID_SIZE));

        // Directions for movement: up, down, left, right
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        q.push(start);
        visited.insert(start);

        while (!q.empty())
        {
            Position curr = q.front();
            q.pop();

            // If we reach the target position
            if (curr == end)
            {
                while (curr != start)
                {
                    path.push_back(curr);
                    curr = parent[curr.x][curr.y];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }

            // Explore neighbors
            for (auto &dir : directions)
            {
                Position neighbor = {curr.x + dir[0], curr.y + dir[1]};
                if (isValid(neighbor, grid) && visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    visited.insert(neighbor);
                    parent[neighbor.x][neighbor.y] = curr;
                }
            }
        }
        return path; // Return empty path if no valid path exists
    }

    static void initializeGrid(vector<vector<int>> &grid)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            for (int j = 0; j < GRID_SIZE; ++j)
            {
                grid[i][j] = 0; // 0 indicates free space
            }
        }
    }

private:
    static bool isValid(Position pos, vector<vector<int>> &grid)
    {
        return pos.x >= 0 && pos.x < GRID_SIZE && pos.y >= 0 && pos.y < GRID_SIZE && grid[pos.x][pos.y] == 0;
    }
};

#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Position.h"
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int GRID_SIZE = 10;

class Grid
{
public:
    static vector<Position> findPath(Position start, Position end, vector<vector<int>> &grid)
    {
        vector<Position> path;
        queue<Position> q;
        unordered_set<Position> visited;
        vector<vector<Position>> parent(GRID_SIZE, vector<Position>(GRID_SIZE));

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movement: up, down, left, right

        q.push(start);
        visited.insert(start);

        while (!q.empty())
        {
            Position curr = q.front();
            q.pop();

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

            for (auto &dir : directions)
            {
                Position neighbor(curr.x + dir[0], curr.y + dir[1]);
                if (isValid(neighbor, grid) && visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    visited.insert(neighbor);
                    parent[neighbor.x][neighbor.y] = curr;
                }
            }
        }

        return path;
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
    static bool isValid(Position pos, const vector<vector<int>> &grid)
    {
        return pos.x >= 0 && pos.x < GRID_SIZE && pos.y >= 0 && pos.y < GRID_SIZE && grid[pos.x][pos.y] == 0;
    }
};

#endif

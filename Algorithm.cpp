#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib> // for rand()
#include<bits/stdc++.h>
#include "./models/Enemy.h"
#include "./models/Player.h"

using namespace std;

const int GRID_SIZE = 5;
char grid[GRID_SIZE][GRID_SIZE];
//int playerX, playerY, enemyX, enemyY;

class MovementAlgorithm {
public:
    virtual void move(Enemy enemy,Player player) = 0; // Pure virtual method for movement
    virtual ~MovementAlgorithm() {}
};
class ShortestPathAlgorithm : public MovementAlgorithm {
public:
    void move(Enemy enemy,Player player) override {
        vector<vector<int>> distance(GRID_SIZE, vector<int>(GRID_SIZE, INT_MAX));
        vector<vector<pair<int, int>>> parent(GRID_SIZE, vector<pair<int, int>>(GRID_SIZE, {-1, -1}));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

        distance[enemy.getenemyX()][enemy.getenemyY()] = 0;
        pq.emplace(0, enemy.getenemyX(), enemy.getenemyY());

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [cost, x, y] = pq.top();
            pq.pop();

            if (x == player.getPlayerX() && y == player.getPlayerY()) break;

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];

                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && grid[nx][ny] != '#' && distance[nx][ny] > cost + 1) {
                    distance[nx][ny] = cost + 1;
                    pq.emplace(distance[nx][ny], nx, ny);
                    parent[nx][ny] = {x, y};
                }
            }
        }

        // Reconstruct path and move enemy
        int cx = player.getPlayerX(), cy = player.getPlayerY();
        while (parent[cx][cy] != make_pair(enemy.getenemyX(), enemy.getenemyY()) && parent[cx][cy] != make_pair(-1, -1)) {
            tie(cx, cy) = parent[cx][cy];
        }

        grid[enemy.getenemyX()][enemy.getenemyY()] = '.'; // Clear old position
        enemy.setEnemyX(cx);
        enemy.setEnemyY(cy);
        grid[cx][cy] = 'E'; // Mark new position

        cout << "Enemy moved to (" << cx << ", " << cy<< ") using Shortest Path." << endl;
    }
};

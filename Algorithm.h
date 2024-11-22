
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <vector>

const int GRID_SIZE = 5;
extern char grid[GRID_SIZE][GRID_SIZE];

class MovementAlgorithm {
public:
    virtual void move() = 0;
    virtual ~MovementAlgorithm() {}
};

class ShortestPathAlgorithm : public MovementAlgorithm {
public:
    void move(Enemy enemy,Player player) override;
};

class RandomMovementAlgorithm : public MovementAlgorithm {
public:
    void move(Enemy enemy,Player player) override;
};

#endif // ALGORITHM_H

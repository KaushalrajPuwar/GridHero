#ifndef POSITION_H
#define POSITION_H

#include <functional> // For std::hash

class Position
{
public:
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Position &other) const
    {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

// Define a hash function to use Position in unordered_set or unordered_map
namespace std
{
    template <>
    struct hash<Position>
    {
        size_t operator()(const Position &p) const
        {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

#endif

#ifndef MATCH_H
#define MATCH_H

#include <vector>
#include <algorithm>

#include "Board.h"

namespace mthree {

struct Match
{
public:
    Match(const std::vector<BoardPos>& positions):
    positions(positions)
    {
        std::sort(this->positions.begin(), this->positions.end());
    }

    inline const std::vector<BoardPos>& getPositions() const { return this->positions; }

    inline bool isBetterThan(const Match& other) const
    {
        return (this->positions.size() >= other.positions.size());
    }

    inline bool isInTheWayOf(const Match& other) const
    {
        std::vector<BoardPos> intersections;

        std::set_intersection(
            this->positions.begin(), this->positions.end(),
            other.positions.begin(), other.positions.end(),
            intersections.begin()
        );

        return (!intersections.empty());
    }

public:
    bool operator==(const Match& other) const
    {
        return (this->positions == other.positions);
    }

private:
    std::vector<BoardPos> positions;

};

} // namespace mthree

#endif /* MATCH_H */
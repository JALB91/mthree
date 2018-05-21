#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

#include "Match.h"
#include "Board.h"
#include "Pos.h"

namespace mthree {

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();

    bool step(Board& board) const;
    bool computeMatches(Board& board) const;

    std::vector<Match> getValidMatches(const Board& board) const;

    bool canSwap(const Board& board, const BoardPos& a, const BoardPos& b) const;
    void trySwap(Board& board, const BoardPos& a, const BoardPos& b) const;

protected:
	BoardDir getOppositeDirectionOf(const BoardDir& dir) const;

    std::vector<BoardPos> getAdjacentsMatching(const Board& board, const BoardPos& pos, std::vector<BoardPos>& exclude) const;
    std::vector<Match> composeValidMatches(const std::vector<BoardPos>& adjacents) const;
    void filterPosBy(std::vector<std::vector<BoardPos>>& out, const std::vector<BoardPos>& from, const std::function<bool(const BoardPos&, const BoardPos&)>& comparator) const;

    void computeMatch(Board& board, const Match& match) const;

    void explodeItemAt(Board& board, const BoardPos& pos) const;
    void explodeComboAt(Board& board, const BoardPos& a, const BoardPos& b) const;

private:
    const BoardDir gravity;

};

} // namespace mthree

#endif /* GAME_LOGIC_H */
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

#include "GameState.h"
#include "Match.h"
#include "Board.h"
#include "Pos.h"

namespace mthree {

class GameLogic
{
public:
    GameLogic(const Board& board);
    ~GameLogic();

    inline const Board& getBoard() const { return this->board; }

    bool canSwap(const BoardPos& a, const BoardPos& b);

    void trySwap(const BoardPos& a, const BoardPos& b);

protected:
    void updateMatches();
    std::vector<BoardPos> getAdjacentsMatching(const BoardPos& pos, std::vector<BoardPos>& exclude);
    std::vector<Match> composeValidMatches(const std::vector<BoardPos>& adjacents);
    void filterPosBy(std::vector<std::vector<BoardPos>>& out, const std::vector<BoardPos>& from, const std::function<bool(const BoardPos&, const BoardPos&)>& comparator);

    inline bool hasMatches() const { return (!this->matches.empty()); }
    inline std::vector<Match> getMatches() const { return this->matches; }

    void computeMatch(const Match& match);

    void explodeItemAt(const BoardPos& pos);
    void explodeComboAt(const BoardPos& a, const BoardPos& b);

private:
    Board board;
    GameState state;

    std::vector<Match> matches;

};

} // namespace mthree

#endif /* GAME_LOGIC_H */
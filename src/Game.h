#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Board.h"
#include "GameLogic.h"
#include "GameState.h"
#include "Match.h"

namespace mthree {

class Game
{
public:
    Game();
    ~Game();

    inline const Board& getBoard() const { return this->board; }
    inline const GameLogic& getLogic() const { return this->logic; }
    inline const GameState& getState() const { return this->state; }

    void startNewGame();
    void step();

protected:

private:
    Board board;
    GameLogic logic;
    GameState state;

    std::vector<Match> validMatches;

};

} // namespace mthree

#endif /* GAME_H */
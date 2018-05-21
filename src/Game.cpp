#include "Game.h"
#include "Tile.h"
#include "Generator.h"

#include <vector>

using namespace std;

namespace mthree {

Game::Game():
state(GameState::SETUP)
{

}

Game::~Game()
{

}


void Game::startNewGame()
{
    vector<Tile> tiles;

    for (int x = 0; x < 5; ++x)
    {
        for (int y = 0; y < 5; ++y)
        {
            tiles.push_back(move(Tile{BoardPos{x, y}, GameItem::getRandomItem()}));
        }
    }

    vector<Generator> generators;

    for (int x = 0; x < 5; x++)
    {
        generators.push_back(Generator{BoardPos{x, -1}});
    }

    this->board = Board{tiles, generators};
    this->state = GameState::MATCHING;
}

void Game::step()
{
    switch (this->state)
    {
        case GameState::MATCHING:
        {
            if (this->logic.computeMatches(this->board) ||
                this->logic.step(this->board))
            {
                this->state = GameState::STEPPING;
            }
            else
            {
                this->state = GameState::USER_INTERACTION;
            }
            break;
        }
        case GameState::STEPPING:
        {
            if (this->logic.step(this->board))
            {
                this->logic.computeMatches(this->board);
            }
            else
            {
                this->state = GameState::USER_INTERACTION;
            }
            break;
        }
        case GameState::SETUP:
        default:
            break;
    }
}

} // namespace mthree
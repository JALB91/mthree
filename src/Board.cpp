#include "Board.h"

using namespace std;

namespace mthree {

Board::Board(const map<BoardPos, Tile>& tilesMap):
tilesMap(tilesMap)
{
    for (const auto& pair: tilesMap)
    {
        this->width = std::max(this->width, pair.first.x);
        this->height = std::max(this->height, pair.first.y);
    }
}

Board::~Board()
{
    
}

} //namespace mthree
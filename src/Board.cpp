#include "Board.h"

using namespace std;

namespace mthree {

Board::Board(const map<BoardPos, Tile>& tilesMap):
tilesMap(tilesMap)
{
    for (const auto& pair: tilesMap)
    {
        this->width = std::max(this->width, static_cast<uint8_t>(pair.first.x + 1));
        this->height = std::max(this->height, static_cast<uint8_t>(pair.first.y + 1));
    }
}

Board::~Board()
{
    
}


bool Board::hasTile(const BoardPos& pos)
{
    return (this->tilesMap.find(pos) != this->tilesMap.end());
}

} //namespace mthree
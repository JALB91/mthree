#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <cstdint>

#include "Pos.h"
#include "Tile.h"

namespace mthree {

class Board
{
public:
    Board(const std::map<BoardPos, Tile>& tilesMap);
    ~Board();

    inline const std::map<BoardPos, Tile>& getTilesMap() const { return this->tilesMap; }
    inline const uint8_t getBoardHeight() const { return this->height; }
    inline const uint8_t getBoardWidth() const { return this->width; }

protected:

private:
    std::map<BoardPos, Tile> tilesMap;
    uint8_t height = 0;
    uint8_t width = 0;

};

} // namespace mthree

#endif /* BOARD_H */

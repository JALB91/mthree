#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include <cstdint>
#include <assert.h>

#include "Pos.h"
#include "Tile.h"
#include "BoardDir.h"

namespace mthree {

class Board
{
public:
    Board(const std::map<BoardPos, Tile>& tilesMap);
    ~Board();

    inline const std::map<BoardPos, Tile>& getTilesMap() const { return this->tilesMap; }
    inline const uint8_t getHeight() const { return this->height; }
    inline const uint8_t getWidth() const { return this->width; }
    
	Tile& getTileAt(const BoardPos& pos);
	Tile& getAdjacentTile(const Tile& tile, const BoardDir& dir);
	std::vector<Tile&> getAdjacentTiles(const BoardPos& pos);
	std::vector<Tile&> getAdjacentTiles(const Tile& tile);

	BoardPos getAdjacentPos(const BoardPos& pos, const BoardDir& dir) const;

	bool hasTile(const BoardPos& pos) const;
	bool hasAdjacentTile(const BoardPos& pos, const BoardDir& dir) const;
    
protected:

private:
    std::map<BoardPos, Tile> tilesMap;
    uint8_t height = 0;
    uint8_t width = 0;

};

} // namespace mthree

#endif /* BOARD_H */

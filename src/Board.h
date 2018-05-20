#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdint>

#include "Pos.h"
#include "Tile.h"
#include "Generator.h"
#include "BoardDir.h"

namespace mthree {

class Board
{
public:
    Board(const std::vector<Tile>& tilesMap, const std::vector<Generator>& generators);
    ~Board();

    inline std::vector<Tile>& getTiles() { return this->tiles; }
	inline const std::vector<Generator>& getGenerators() const { return this->generators; }

    inline const uint8_t getHeight() const { return this->height; }
    inline const uint8_t getWidth() const { return this->width; }

	const Tile* getTileAt(const BoardPos& pos) const;
	const Tile* getAdjacentTile(const Tile* tile, const BoardDir& dir) const;
    
	Tile* getTileAt(const BoardPos& pos);
	Tile* getAdjacentTile(const Tile* tile, const BoardDir& dir);

    std::vector<Tile*> getAdjacentTiles(const Tile *tile);
    std::vector<Tile*> getAdjacentTiles(const BoardPos& pos);

    std::vector<BoardPos> getAllAdjacentPos(const BoardPos& pos) const;
	BoardPos getAdjacentPos(const BoardPos& pos, const BoardDir& dir) const;

	Generator* getGeneratorAt(const BoardPos& pos);

	bool hasTile(const BoardPos& pos) const;
	bool hasAdjacentTile(const BoardPos& pos, const BoardDir& dir) const;

	bool hasGenerator(const BoardPos& pos) const;
	bool hasAdjacentGenerator(const BoardPos& pos, const BoardDir& dir) const;
    
protected:

private:
    std::vector<Tile> tiles;
	std::vector<Generator> generators;

    uint8_t height = 0;
    uint8_t width = 0;

};

} // namespace mthree

#endif /* BOARD_H */

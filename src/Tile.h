#ifndef TILE_H
#define TILE_H

#include "Pos.h"
#include "GameItem.h"

namespace mthree {

class Tile
{
public:
	Tile(const BoardPos& p = BoardPos{0, 0}, const GameItem& item = GameItem{});
    ~Tile();

	inline const BoardPos& getPos() const { return this->pos; }

    inline const GameItem& getItem() const { return this->item; }
    inline void setItem(const GameItem& item) { this->item = item; }

    bool hasItem() const;

protected:
	BoardPos pos;
    GameItem item;

private:
    
};

} // namespace mthree

#endif /* TILE_H */
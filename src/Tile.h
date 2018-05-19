#ifndef TILE_H
#define TILE_H

#include "GameItem.h"

namespace mthree {

class Tile
{
public:
    Tile(const GameItem& item = GameItem{});
    ~Tile();

    inline const GameItem& getItem() const { return item; }
    inline void setItem(const GameItem& item) { this->item = item; }

    bool hasItem() const;

protected:
    GameItem item;

private:
    
};

} // namespace mthree

#endif /* TILE_H */
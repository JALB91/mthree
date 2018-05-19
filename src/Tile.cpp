#include "Tile.h"

namespace mthree {

Tile::Tile(const BoardPos& pos /* = BoardPos{} */, const GameItem& item /* = GameItem{} */):
pos(pos),
item(item)
{

}

Tile::~Tile()
{

}


bool Tile::hasItem() const
{
    return (this->item.getType() != ItemType::EMPTY && this->item.getColor() != ItemColor::NO_COLOR);
}

} // namespace mthree
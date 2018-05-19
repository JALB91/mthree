#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "ItemType.h"
#include "ItemColor.h"

namespace mthree {

class GameItem
{
public:
    GameItem(const ItemType& type = ItemType::EMPTY, const ItemColor& color = ItemColor::NO_COLOR);
    ~GameItem();

    inline const ItemType& getType() const { return type; }
    inline const ItemColor& getColor() const { return color; }

protected:
    ItemType type;
    ItemColor color;

private:

};

} // namespace mthree

#endif /* GAME_ITEM_H */
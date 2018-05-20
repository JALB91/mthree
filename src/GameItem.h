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

public:
    bool operator==(const GameItem& other) const
    {
        if ((this->type == ItemType::CUBE && other.type == ItemType::CUBE) ||
            (this->type == ItemType::EMPTY && other.type == ItemType::EMPTY))
        {
            return true;
        }

        return (this->type == other.type && this->color == other.color);
    }

protected:
    ItemType type;
    ItemColor color;

private:

};

} // namespace mthree

#endif /* GAME_ITEM_H */
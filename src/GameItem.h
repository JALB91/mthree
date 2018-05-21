#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <cstdint>

#include "ItemType.h"
#include "ItemColor.h"

namespace mthree {

class GameItem
{
public:
    using ITEM_ID = uint64_t;
    static ITEM_ID next_id;

public:
	static const GameItem EMPTY_ITEM;

    static GameItem getRandomItem();

public:
    GameItem(const ItemType& type = ItemType::EMPTY, const ItemColor& color = ItemColor::NO_COLOR);
    ~GameItem();

    inline const ItemType& getType() const { return this->type; }
    inline const ItemColor& getColor() const { return this->color; }
    inline const ITEM_ID& getItemId() const { return this->id; }

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
    ITEM_ID id;

};

} // namespace mthree

#endif /* GAME_ITEM_H */
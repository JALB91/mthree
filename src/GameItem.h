#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "ItemType.h"

namespace mthree {

class GameItem
{
public:
    GameItem(const ItemType& type);
    ~GameItem();

    inline const ItemType& getItemType() const { return type; }

protected:
    const ItemType& type;

private:

};

} // namespace mthree

#endif /* GAME_ITEM_H */
#include "GameItem.h"

namespace mthree {

const GameItem GameItem::EMPTY_ITEM = GameItem{ ItemType::EMPTY, ItemColor::NO_COLOR };

GameItem::GameItem(
    const ItemType& type /* = ItemType::EMPTY */, 
    const ItemColor& color /* = ItemColor::NO_COLOR */
    ):
type(type),
color(color)
{

}

GameItem::~GameItem()
{
    
}

} // namespace mthree
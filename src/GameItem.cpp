#include "GameItem.h"
#include "RandHelper.h"

namespace mthree {

GameItem::ITEM_ID GameItem::next_id = 0;

const GameItem GameItem::EMPTY_ITEM = GameItem{ ItemType::EMPTY, ItemColor::NO_COLOR };

GameItem GameItem::getRandomItem()
{
    int color = RandHelper::getInstance()->getNextRandom() % ALL_COLORS.size();
    return GameItem{ItemType::ITEM, static_cast<ItemColor>(color)};
}

GameItem::GameItem(
    const ItemType& type /* = ItemType::EMPTY */, 
    const ItemColor& color /* = ItemColor::NO_COLOR */
    ):
type(type),
color(color),
id(++GameItem::next_id)
{

}

GameItem::~GameItem()
{
    
}

} // namespace mthree
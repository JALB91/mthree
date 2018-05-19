#include "GameItem.h"

namespace mthree {

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
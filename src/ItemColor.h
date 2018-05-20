#ifndef ITEM_COLOR_H
#define ITEM_COLOR_H

#include <vector>

namespace mthree {

enum class ItemColor
{
    RED,
    BLUE,
    GREEN,
    YELLOW,
    NO_COLOR
};

const std::vector<ItemColor> ALL_COLORS = { ItemColor::RED, ItemColor::BLUE, ItemColor::GREEN, ItemColor::YELLOW };

} // namespace mthree

#endif /* ITEM_COLOR_H */
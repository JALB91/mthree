#include "Generator.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

namespace mthree {

Generator::Generator(const BoardPos& pos):
pos(pos)
{

}

Generator::~Generator()
{

}


GameItem Generator::generate() const
{
	srand(time(NULL));
	int color = rand() % ALL_COLORS.size();
	return GameItem{ ItemType::ITEM, static_cast<ItemColor>(color) };
}

} // namespace mthree
#include "Generator.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

namespace mthree {

Generator::Generator(const BoardPos&& pos):
pos(pos)
{
	
}

Generator::Generator(const BoardPos& pos):
pos(pos)
{
	
}

Generator::~Generator()
{

}


GameItem Generator::generate() const
{
	return GameItem::getRandomItem();
}

} // namespace mthree
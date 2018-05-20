#include <iostream>

#include "Board.h"
#include "GameUtils.h"

using namespace std;
using namespace mthree;

int main()
{
    std::map<BoardPos, Tile> tilesMap;

    for (uint8_t x = 0; x < 5; x++)
    {
        for (uint8_t y = 0; y < 5; y++)
        {
            const BoardPos pos {x, y};
            
            tilesMap[pos] = Tile{pos, GameItem{ItemType::BOMB, ItemColor::BLUE}};
        }
    }

    Board b {tilesMap};

	while (auto c = getc(stdin))
	{
		if (c == 'q')
		{
			break;
		}

		utils::printBoard(b);
	}
    
    return 0;
}

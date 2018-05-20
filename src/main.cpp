#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Board.h"
#include "GameLogic.h"
#include "GameUtils.h"

using namespace std;
using namespace mthree;

int main()
{
    vector<Tile> tiles;

	srand(time(NULL));

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            const BoardPos pos {x, y};
			int color = rand() % ALL_COLORS.size();
            tiles.push_back(Tile{pos, GameItem{ItemType::ITEM, static_cast<ItemColor>(color)}});
        }
    }

	vector<Generator> generators;

	for (int x = 0; x < 5; x++)
	{
		const BoardPos pos{ x, -1 };
		generators.push_back(Generator{pos});
	}

	GameLogic gameLogic{ Board{tiles, generators} };
	gameLogic.step();

	while (auto c = getc(stdin))
	{
		if (c == 'q')
		{
			break;
		}
		else if (c == 'p')
		{
			utils::printBoard(gameLogic.getBoard());
		}
		else if (c == 'm')
		{
			gameLogic.trySwap(BoardPos{ 0, 0 }, BoardPos{ 1, 0 });
		}
	}
    
    return 0;
}

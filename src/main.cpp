#include <iostream>

#include "Game.h"
#include "GameUtils.h"

using namespace std;
using namespace mthree;

int main()
{
    Game game;
	
	while (auto c = getc(stdin))
	{
		if (c == 'q')
		{
			break;
		}
		else if (c == 'n')
		{
			game.startNewGame();
		}
		else if (c == 'p')
		{
			utils::printBoard(game.getBoard());
		}
		else if (c == 's')
		{
			game.step();
		}
		else if (c == 'm')
		{
			// gameLogic.trySwap(BoardPos{ 0, 0 }, BoardPos{ 1, 0 });
		}
		else if (c != '\n')
		{
			cout << c << endl;
		}
	}
    
    return 0;
}

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <iostream>
#include <string>

#include "Board.h"
#include "GameItem.h"

using namespace mthree;
using namespace std;

namespace utils {

string gameItemToString(const GameItem& item)
{
    string type = "";
    string color = "";

    switch (item.getType())
    {
        case ItemType::ITEM:
            type = "i";
            break;
        case ItemType::ROW_H:
            type = "H";
            break;
        case ItemType::ROW_V:
            type = "V";
            break;
        case ItemType::BOMB:
            type = "B";
            break;
        case ItemType::CUBE:
            type = "C";
            break;
        default:
            type = " ";
            break;
    }

    switch (item.getColor())
    {
        case ItemColor::RED:
            color = "r";
            break;
        case ItemColor::BLUE:
            color = "b";
            break;
        case ItemColor::GREEN:
            color = "g";
            break;
        case ItemColor::YELLOW:
            color = "y";
            break;
        default:
            color = " ";
            break;
    }

    return (type + color);
}

void printRow(int width)
{
    for (uint8_t x = 0; x < width; ++x)
    {
        cout << "- -- ";
    }

    cout << "-" << endl;
}

void printBoard(const Board& board)
{
    string boardStr = "";

    printRow(board.getWidth());

    for (uint8_t y = 0; y < board.getHeight(); ++y)
    {
        cout << "|";

        for (uint8_t x = 0; x < board.getWidth(); ++x)
        {
            BoardPos p {x, y};

			if (board.hasTile(p))
			{
				cout << " " + gameItemToString(board.getTileAt(p)->getItem()) << " |";
			}
			else
			{
				cout << "    |";
			}
        }

        cout << endl;

        printRow(board.getWidth());
    }
}

} // namespace utils

#endif /* GAME_UTILS_H */
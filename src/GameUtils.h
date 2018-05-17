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
    switch (item.getItemType())
    {
        case ItemType::ITEM_1:  return "A";
        default:                return "";
    }
}

void printRow(int width)
{
    for (int x = 0; x < width; x++)
    {
        cout << "- - ";
    }

    cout << "-" << endl;
}

void printBoard(const Board& board)
{
    string boardStr = "";

    printRow(board.getBoardWidth());

    for (int y = 0; y < board.getBoardHeight(); y++)
    {
        cout << "|";

        for (int x = 0; x < board.getBoardWidth(); x++)
        {
            cout << " " + gameItemToString(GameItem{ItemType::ITEM_1}) << " |";
        }

        cout << endl;

        printRow(board.getBoardWidth());
    }
}

} // namespace utils

#endif /* GAME_UTILS_H */
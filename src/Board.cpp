#include "Board.h"

#include <algorithm>
#include <assert.h>

using namespace std;

namespace mthree {

Board::Board(const map<BoardPos, Tile>& tilesMap):
tilesMap(tilesMap)
{
    for (const auto& pair: tilesMap)
    {
        this->width = std::max(this->width, static_cast<uint8_t>(pair.first.x + 1));
        this->height = std::max(this->height, static_cast<uint8_t>(pair.first.y + 1));
    }
}

Board::~Board()
{
    
}


Tile* Board::getTileAt(const BoardPos& pos)
{
	return this->hasTile(pos) ? &this->tilesMap.at(pos) : nullptr;
}

Tile* Board::getAdjacentTile(const Tile* tile, const BoardDir& dir)
{
	if (!tile) return nullptr;
	return this->getTileAt(this->getAdjacentPos(tile->getPos(), dir));
}


vector<Tile*> Board::getAdjacentTiles(const Tile* tile)
{
	if (!tile) return {};

	vector<Tile*> result;

	for (const BoardDir& dir: ALL_DIRS)
	{
		if (auto adjacent = this->getAdjacentTile(tile, dir))
		{
			result.push_back(adjacent);
		}
	}

	return result;
}

vector<Tile*> Board::getAdjacentTiles(const BoardPos &pos)
{
	return this->getAdjacentTiles(this->getTileAt(pos));
}


vector<BoardPos> Board::getAllAdjacentPos(const BoardPos& pos) const
{
	vector<BoardPos> result;

	for (const BoardDir& dir: ALL_DIRS)
	{
		result.push_back(this->getAdjacentPos(pos, dir));
	}

	return result;
}

BoardPos Board::getAdjacentPos(const BoardPos& pos, const BoardDir& dir) const
{
	int offsetX = 0;
	int offsetY = 0;

	switch (dir)
	{
	case BoardDir::UP:
		offsetY = 1;
		break;
	case BoardDir::DOWN:
		offsetY = -1;
		break;
	case BoardDir::RIGHT:
		offsetX = 1;
		break;
	case BoardDir::LEFT:
		offsetX = -1;
		break;
	}

	const BoardPos result{ pos.x + offsetX, pos.y + offsetY };

	return BoardPos{ pos.x + offsetX, pos.y + offsetY };
}


bool Board::hasTile(const BoardPos& pos) const
{
    return (this->tilesMap.find(pos) != this->tilesMap.cend());
}

bool Board::hasAdjacentTile(const BoardPos& pos, const BoardDir& dir) const
{
	return this->hasTile(this->getAdjacentPos(pos, dir));
}

} //namespace mthree
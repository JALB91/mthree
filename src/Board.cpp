#include "Board.h"

#include <algorithm>
#include <assert.h>

using namespace std;

namespace mthree {

Board::Board(const vector<Tile>& tiles, const vector<Generator>& generators):
tiles(tiles),
generators(generators)
{
    for (const Tile& tile: tiles)
    {
        this->width = std::max(this->width, static_cast<uint8_t>(tile.getPos().x + 1));
		this->height = std::max(this->height, static_cast<uint8_t>(tile.getPos().y + 1));
    }
}

Board::~Board()
{
    
}


const Tile* Board::getTileAt(const BoardPos& pos) const
{
	if (this->hasTile(pos))
	{
		auto it = find_if(this->tiles.cbegin(), this->tiles.cend(), [pos](const Tile& tile) {
			return (tile.getPos() == pos);
		});

		return &(*it);
	}
	else
	{
		return nullptr;
	}
}

const Tile* Board::getAdjacentTile(const Tile* tile, const BoardDir& dir) const
{
	if (!tile) return nullptr;
	return this->getTileAt(this->getAdjacentPos(tile->getPos(), dir));
}


Tile* Board::getTileAt(const BoardPos& pos)
{
	if (this->hasTile(pos))
	{
		auto it = find_if(this->tiles.begin(), this->tiles.end(), [pos](const Tile& tile) {
			return (tile.getPos() == pos);
		});

		return &(*it);
	}
	else
	{
		return nullptr;
	}
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
		offsetY = -1;
		break;
	case BoardDir::DOWN:
		offsetY = 1;
		break;
	case BoardDir::RIGHT:
		offsetX = 1;
		break;
	case BoardDir::LEFT:
		offsetX = -1;
		break;
	}

	return BoardPos{ pos.x + offsetX, pos.y + offsetY };
}


Generator* Board::getGeneratorAt(const BoardPos& pos)
{
	auto it = find_if(this->generators.cbegin(), this->generators.cend(), [pos](const Generator& generator) {
		return (generator.getPos() == pos);
	});

	return (it != this->generators.cend() ? &(*it) : nullptr);
}


bool Board::hasTile(const BoardPos& pos) const
{
	auto it = find_if(this->tiles.begin(), this->tiles.end(), [pos](const Tile& tile) {
		return (tile.getPos() == pos);
	});
    return (it != this->tiles.end());
}

bool Board::hasAdjacentTile(const BoardPos& pos, const BoardDir& dir) const
{
	return this->hasTile(this->getAdjacentPos(pos, dir));
}


bool Board::hasGenerator(const BoardPos& pos) const
{
	auto it = find_if(this->generators.begin(), this->generators.end(), [pos](const Generator& generator) {
		return (generator.getPos() == pos);
	});
	return (it != this->generators.end());
}

bool Board::hasAdjacentGenerator(const BoardPos& pos, const BoardDir& dir) const
{
	return this->hasGenerator(this->getAdjacentPos(pos, dir));
}

} //namespace mthree
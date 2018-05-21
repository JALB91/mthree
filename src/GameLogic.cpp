#include "GameLogic.h"

using namespace std;

namespace mthree {

bool sortByRow(const BoardPos& a, const BoardPos& b) { return ((a.y < b.y) || (a.y == b.y && a.x < b.x)); }
bool sortByCol(const BoardPos& a, const BoardPos& b) { return ((a.x < b.x) || (a.x == b.x && a.y < b.y)); }

GameLogic::GameLogic():
gravity(BoardDir::DOWN)
{
    
}

GameLogic::~GameLogic()
{

}


BoardDir GameLogic::getOppositeDirectionOf(const BoardDir& dir) const
{
	switch (dir)
	{
		case BoardDir::UP:		return BoardDir::DOWN;
		case BoardDir::RIGHT:	return BoardDir::LEFT;
		case BoardDir::DOWN:	return BoardDir::UP;
		case BoardDir::LEFT:	return BoardDir::RIGHT;
	}
}


bool GameLogic::step(Board& board) const
{
    bool result = false;

	for (Tile& tile: board.getTiles())
	{
		const BoardPos& p = tile.getPos();

		if (!tile.hasItem())
		{
			const BoardPos& adjacent = board.getAdjacentPos(p, this->getOppositeDirectionOf(this->gravity));
			Tile* other = board.getTileAt(adjacent);

			if (other && other->hasItem())
			{
				tile.setItem(other->getItem());
				other->setItem(GameItem::EMPTY_ITEM);

                result = true;
			}
			else if (const Generator* generator = board.getGeneratorAt(adjacent))
			{
				tile.setItem(generator->generate());

                result = true;
			}
		}
	}

    return result;
}

bool GameLogic::computeMatches(Board& board) const
{
    vector<Match> matches = this->getValidMatches(board);

    for (const Match& match: matches)
    {
        this->computeMatch(board, match);
    }

    return !matches.empty();
}


bool GameLogic::canSwap(const Board& board, const BoardPos& a, const BoardPos& b) const
{
    const vector<BoardPos> adjacents = board.getAllAdjacentPos(a);

    if (find(adjacents.cbegin(), adjacents.cend(), b) == adjacents.cend())
    {
        // "a" or "b" are not valid
        return false;
    }

    const Tile* tA = board.getTileAt(a);
    const Tile* tB = board.getTileAt(b);

    if (tA && tB)
    {
        // Only checking if there is something to swap
        return tA->hasItem() && tB->hasItem();
    }

    return false;
}

void GameLogic::trySwap(Board& board, const BoardPos& a, const BoardPos& b) const
{
    if (!canSwap(board, a, b)) return;

    Tile* tA = board.getTileAt(a);
    Tile* tB = board.getTileAt(b);

    GameItem giA = tA->getItem();
    GameItem giB = tB->getItem();

    if ((giA.getType() == ItemType::ITEM || giB.getType() == ItemType::ITEM) &&
        (giA.getType() != ItemType::CUBE && giB.getType() != ItemType::CUBE))
    {
        // Swap the two game items
        tA->setItem(giB);
        tB->setItem(giA);

        // Update current matches on the board
        const vector<Match>& matches = this->getValidMatches(board);

        if (!matches.empty())
        {
            // Compute them
        }
        else
        {
            // Revert the swap
            tA->setItem(giA);
            tB->setItem(giB);
        }
    }
    else
    {
        // Matching combo
    }
}


vector<Match> GameLogic::getValidMatches(const Board& board) const
{
    vector<Match> matches;

    for (int y = 0; y < board.getHeight(); ++y)
    {
        for (int x = 0; x < board.getWidth(); ++x)
        {
            const BoardPos currentPos { x, y };

            auto it = find_if(matches.begin(), matches.end(), [currentPos] (const Match& match) {
                const vector<BoardPos>& positions = match.getPositions();
                return (find(positions.cbegin(), positions.cend(), currentPos) != positions.cend());
            });

            // Not checking positions already computed
            if (it != matches.end() || !board.getTileAt(currentPos)) continue;

            vector<BoardPos> exclude;
            vector<Match> newMatches = this->composeValidMatches(this->getAdjacentsMatching(board, currentPos, exclude));

            matches.insert(matches.end(), newMatches.begin(), newMatches.end());
        }
    }

	for (int i = 0; i < matches.size(); ++i)
	{
		const Match& current = matches[i];

		for (const Match& other: matches)
		{
			if (find(matches.cbegin(), matches.cend(), other) == find(matches.cbegin(), matches.cend(), current)) continue;

			if (current == other || (current.isInTheWayOf(other) && !current.isBetterThan(other)))
			{
				matches.erase(matches.begin() + i);
				i--;
				break;
			}
		}
	}

    return matches;
}

vector<BoardPos> GameLogic::getAdjacentsMatching(const Board& board, const BoardPos& pos, vector<BoardPos>& exclude) const
{
    const Tile* currentTile = board.getTileAt(pos);

    if (!currentTile || !currentTile->hasItem()) return {};

    const GameItem& currentItem = currentTile->getItem();

    if (currentItem.getType() == ItemType::CUBE || currentItem.getType() == ItemType::EMPTY)
    {
        // Cube and Empty item types does not match
        return {};
    }

    vector<BoardPos> result { pos };
    vector<BoardPos> adjacents = board.getAllAdjacentPos(pos);

    exclude.push_back(pos);

    for (const BoardPos& adj: adjacents)
    {
        if (find(exclude.cbegin(), exclude.cend(), adj) != exclude.cend())
        {
            continue;
        }

        const Tile* adjTile = board.getTileAt(adj);

        if (!adjTile || !adjTile->hasItem()) continue;

        const GameItem& adjItem = adjTile->getItem();

        if (adjItem.getColor() == currentItem.getColor())
        {
            // Two items matches if they are of the same color
            vector<BoardPos> adjMatching = getAdjacentsMatching(board, adj, exclude);
            result.insert(result.begin(), adjMatching.begin(), adjMatching.end());
        }
    }

	return result;
}

/*
    The precondition for this method is that the BoardPos vector
    passed as parameter is composed by a contiguous sequence of
    BoardPos which refers to Tiles with matching Items
    (that's why they are passed with the method GameLogic::getAdjacentsMatching)

    The method will return a vector of valid matches from them
*/
vector<Match> GameLogic::composeValidMatches(const vector<BoardPos>& adjacents) const
{
    vector<Match> result;

    vector<BoardPos> adjByRow = adjacents;
    sort(adjByRow.begin(), adjByRow.end(), sortByRow);

    vector<vector<BoardPos>> sameRows;
    this->filterPosBy(sameRows, adjByRow, [] (const BoardPos& a, const BoardPos& b) {
        return (a.y == b.y && a.x == b.x + 1);
    });


    vector<BoardPos> adjByCol = adjacents;
    sort(adjByCol.begin(), adjByCol.end(), sortByCol);

    vector<vector<BoardPos>> sameCols;
    this->filterPosBy(sameCols, adjByCol, [] (const BoardPos& a, const BoardPos& b) {
        return (a.x == b.x && a.y == b.y + 1);
    });

    vector<vector<BoardPos>> allContiguous { sameRows.begin(), sameRows.end() };
    allContiguous.insert(allContiguous.end(), sameCols.begin(), sameCols.end());

    for (const vector<BoardPos>& contiguous: allContiguous)
    {
        if (contiguous.size() >= 3) result.push_back(Match{contiguous});
    }

    return result;
}


void GameLogic::filterPosBy(vector<vector<BoardPos>>& out, const vector<BoardPos>& from, const function<bool(const BoardPos&, const BoardPos&)>& comparator) const
{
    for (const BoardPos& pos: from)
    {
        auto it = find_if(out.begin(), out.end(), [pos, comparator] (const vector<BoardPos>& vec) {
            for (const BoardPos& other: vec)
            {
                if (comparator(pos, other))
                {
                    return true;
                }
            }

            return false;
        });

        if (it != out.end())
        {
            vector<BoardPos>& vec = *it;
            vec.push_back(pos);
        }
        else
        {
            out.push_back({pos});
        }
    }
}


void GameLogic::computeMatch(Board& board, const Match& match) const
{
	for (const BoardPos& pos: match.getPositions())
	{
        if (Tile* tile = board.getTileAt(pos))
        {
            tile->setItem(GameItem::EMPTY_ITEM);
        }
	}
}


void GameLogic::explodeItemAt(Board& board, const BoardPos& pos) const
{

}

void GameLogic::explodeComboAt(Board& board, const BoardPos& a, const BoardPos& b) const
{

}

} //namespace mthree
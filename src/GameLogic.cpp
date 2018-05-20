#include "GameLogic.h"

using namespace std;

namespace mthree {

bool sortByRow(const BoardPos& a, const BoardPos& b) { return ((a.y < b.y) || (a.y == b.y && a.x < b.x)); }
bool sortByCol(const BoardPos& a, const BoardPos& b) { return ((a.x < b.x) || (a.x == b.x && a.y < b.y)); }

GameLogic::GameLogic(const Board& board):
board(board),
state(GameState::USER_INTERACTION)
{

}

GameLogic::~GameLogic()
{

}


bool GameLogic::canSwap(const BoardPos& a, const BoardPos& b)
{
    const vector<BoardPos> adjacents = board.getAllAdjacentPos(a);

    if (find(adjacents.begin(), adjacents.end(), b) == adjacents.end())
    {
        // "a" or "b" are not valid
        return false;
    }

    Tile* tA = this->board.getTileAt(a);
    Tile* tB = this->board.getTileAt(b);

    if (tA && tB)
    {
        // Only checking if there is something to swap
        return tA->hasItem() && tB->hasItem();
    }

    return false;
}

void GameLogic::trySwap(const BoardPos& a, const BoardPos& b)
{
    if (!canSwap(a, b)) return;
    
    this->state = GameState::MATCHING;

    Tile* tA = this->board.getTileAt(a);
    Tile* tB = this->board.getTileAt(b);

    GameItem giA = tA->getItem();
    GameItem giB = tB->getItem();

    if ((giA.getType() == ItemType::ITEM || giB.getType() == ItemType::ITEM) &&
        (giA.getType() != ItemType::CUBE && giB.getType() != ItemType::CUBE))
    {
        // Swap the two game items
        tA->setItem(giB);
        tB->setItem(giA);

        // Update current matches on the board
        this->updateMatches();

        if (this->hasMatches())
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


void GameLogic::updateMatches()
{
    this->matches.clear();

    for (int y = 0; y < this->board.getHeight(); ++y)
    {
        for (int x = 0; x < this->board.getWidth(); ++x)
        {
            const BoardPos currentPos { x, y };

            auto it = find_if(this->matches.begin(), this->matches.end(), [currentPos] (const Match& match) {
                const vector<BoardPos>& positions = match.getPositions();
                return (find(positions.begin(), positions.end(), currentPos) != positions.end());
            });

            // Not checking positions already computed
            if (it != this->matches.end() || !this->board.hasTile(currentPos)) continue;

            vector<BoardPos> exclude;
            vector<Match> newMatches = this->composeValidMatches(this->getAdjacentsMatching(currentPos, exclude));

            this->matches.insert(this->matches.end(), newMatches.begin(), newMatches.end());
        }
    }
}

vector<BoardPos> GameLogic::getAdjacentsMatching(const BoardPos& pos, vector<BoardPos>& exclude)
{
    if (!this->board.hasTile(pos)) return {};

    Tile* currentTile = this->board.getTileAt(pos);

    if (!currentTile->hasItem()) return {};

    const GameItem& currentItem = currentTile->getItem();

    if (currentItem.getType() == ItemType::CUBE || currentItem.getType() == ItemType::EMPTY)
    {
        // Cube and Empty item types does not match
        return {};
    }

    vector<BoardPos> result { pos };
    vector<BoardPos> adjacents = this->board.getAllAdjacentPos(pos);

    exclude.push_back(pos);

    for (const BoardPos& adj: adjacents)
    {
        if (find(exclude.begin(), exclude.end(), adj) != exclude.end())
        {
            continue;
        }

        Tile* adjTile = this->board.getTileAt(adj);

        if (!adjTile->hasItem()) continue;

        const GameItem& adjItem = adjTile->getItem();

        if (adjItem.getColor() == currentItem.getColor())
        {
            // Two items matches if they are of the same color
            vector<BoardPos> adjMatching = this->getAdjacentsMatching(adj, exclude);
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
vector<Match> GameLogic::composeValidMatches(const vector<BoardPos>& adjacents)
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


void GameLogic::filterPosBy(vector<vector<BoardPos>>& out, const vector<BoardPos>& from, const function<bool(const BoardPos&, const BoardPos&)>& comparator)
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


void GameLogic::computeMatch(const Match& match)
{

}


void GameLogic::explodeItemAt(const BoardPos& pos)
{

}

void GameLogic::explodeComboAt(const BoardPos& a, const BoardPos& b)
{

}

} //namespace mthree
#ifndef BOARD_DIR_H
#define BOARD_DIR_H

#include <vector>

enum class BoardDir
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

const std::vector<BoardDir> ALL_DIRS = { BoardDir::UP, BoardDir::DOWN, BoardDir::RIGHT, BoardDir::LEFT };

#endif /* BOARD_DIR_H */

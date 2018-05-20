#ifndef GENERATOR_H
#define GENERATOR_H

#include "Pos.h"
#include "GameItem.h"

namespace mthree {

class Generator
{
public:
	Generator(const BoardPos& p);
	~Generator();

	inline const BoardPos& getPos() const { return this->pos; }

	GameItem generate() const;

private:
	BoardPos pos;

};

} // namespace mthree

#endif /* GENERATOR_H */

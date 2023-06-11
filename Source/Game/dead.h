#pragma once
#include "map.h"
#include "clear_level.h"
#include "move.h"
#include "Object.h"

class Dead {
public:
	Dead();
	bool IfDead(int level, Map map, ClearLevel goal);
private:
	bool IfBoxMoviable(int level, Map map, int x, int y, ObjectType box);
	Move move;
};
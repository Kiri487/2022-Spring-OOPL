#pragma once
#include "map.h"
#include "move.h"
#include "Object.h"

class Dead {
public:
	Dead();
	bool IfDead(int level, Map map);
private:
	bool IfBoxoviable(int level, Map map, int x, int y, ObjectType box);
	Move move;
};
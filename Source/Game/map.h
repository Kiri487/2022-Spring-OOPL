#pragma once
#include <vector>
#include <stack>
#include "Object.h"
#include "move.h"

class Map {
private:
	std::vector<std::vector<Object>> data;
	int level;
	Move movestep;

public:
	int width, height;
	void Matrix(int level);
	void Show();
	void MoveObject(int level, int move);
	void Undo();
	void MapStepClear();
	std::vector<std::vector<Object>> GetNowMap();
	CPoint boxtag(CPoint target, ObjectType boxtype);
	bool boundary(CPoint target, int movetag);
	CPoint ori;
	ObjectType ReturnObjectType(int x, int y);
	string PrintObjectType(int x, int y);
	CPoint bob;
	std::stack<std::vector<std::vector<Object>>> MapStep;
	std::stack<CPoint> BobStep;
	Object objectlist;

};



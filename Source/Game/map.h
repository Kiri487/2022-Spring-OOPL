#pragma once
#include <vector>
#include "Object.h"

class Map {
private:
	std::vector<std::vector<Object>> data;
	int level;
	void MoveObject(int level, int move_tag, int move);

public:
	int width, height;
	void Matrix(int level);
	void Show();
	void MoveObject(int level, int move);
	void movenobox(int level, int move);
	void moveSbox(int level, int move);
	int boxtag(CPoint target, ObjectType boxtype);
	CPoint return_move(int movetag);
	bool boundary(CPoint target, int movetag);
	CPoint ori;
	CPoint ReturnOri(int level);
	ObjectType ReturnObjectType(int x, int y);
	string PrintObjectType(int x, int y);
	CPoint bob;
};



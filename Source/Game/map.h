#pragma once
#include <vector>
#include "Object.h"

class Map {
private:
	std::vector<std::vector<Object>> data;
	int level;

public:
	int width, height;
	void Matrix(int level);
	void Show();
	void MoveObject(int level, int x, int y, int move);
	CPoint ori;
	CPoint ReturnOri(int level);
	ObjectType ReturnObjectType(Object object, int x, int y);
	string PrintObjectType(int x, int y);
};



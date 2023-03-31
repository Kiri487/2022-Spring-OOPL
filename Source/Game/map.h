#pragma once
#include <vector>
#include "Object.h"

class Map {
private:
	int width, height;
	std::vector<std::vector<int>> data;
	int level;

public:
	Map(int width, int height);
	void Matrix(int level);
	void Show(int level);
};



#pragma once
#include <vector>
#include "map.h"

class ClearLevel {
public:
	ClearLevel();
	void GoalLocation(int level);
	int GetValue(int x, int y);
	bool IfClear(int level, Map map);
	int width, height;
private:
	std::vector<std::vector<int>> goal_data;
};
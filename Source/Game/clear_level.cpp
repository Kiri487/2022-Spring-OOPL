#include "stdafx.h"
#include "clear_level.h"
#include <fstream>
#include <string>

ClearLevel::ClearLevel() {

}

void ClearLevel::GoalLocation(int level) {
	std::string filename = "Resources/other_object" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);

	CPoint mapsize;
	ifs >> mapsize.x;
	ifs >> mapsize.y;

	this->width = mapsize.x;
	this->height = mapsize.y;

	goal_data.clear();
	goal_data.resize(mapsize.x, std::vector<int>(mapsize.y));

	for (int i = 0; i < mapsize.y; i++) {
		for (int j = 0; j < mapsize.x; j++) {
			ifs >> goal_data[j][i];
		}
	}

	ifs.close();
}

bool ClearLevel::IfClear(int level, Map map) {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (goal_data[i][j] == 1) {
				int value = map.ReturnObjectType(i, j);
				if (value < 3 || value > 5) {
					return false;
				}
			}
		}
	}
	return true;
}

int ClearLevel::GetValue(int x, int y) {
	return goal_data[x][y];
}
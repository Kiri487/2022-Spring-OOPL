#pragma once
#include <vector>
#include "object.h"

class Move {
private:
	CPoint ori;
public:
	std::vector<std::vector<Object>> movenobox(std::vector<std::vector<Object>> data, int level, int move, CPoint bob);
	std::vector<std::vector<Object>> moveSbox(std::vector<std::vector<Object>> data, int level, int move, CPoint bob);
	std::vector<std::vector<Object>> moveMbox(std::vector<std::vector<Object>> data, int level, int move, int mboxtag, CPoint bob);
	CPoint bobmove(CPoint bob, int move);
	CPoint return_move(int movetag);
	CPoint ReturnOri(int level);
};
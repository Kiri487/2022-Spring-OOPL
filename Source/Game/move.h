#pragma once
#include <vector>
#include "object.h"

class Move {
private:
	CPoint ori;
public:
	std::vector<std::vector<Object>> movenobox(std::vector<std::vector<Object>> data, int level, int move, CPoint bob);
	std::vector<std::vector<Object>> moveSbox(std::vector<std::vector<Object>> data, int level, int move, CPoint bob, ObjectType objecttype);
	std::vector<std::vector<Object>> moveMbox(std::vector<std::vector<Object>> data, int level, int move, CPoint mboxtag, CPoint bob);
	std::vector<std::vector<Object>> moveMSbox(std::vector<std::vector<Object>> data, int level, int move, int mboxtag, CPoint bob, ObjectType objecttype);
	std::vector<std::vector<Object>> moveLbox(std::vector<std::vector<Object>> data, int level, int movetype, CPoint lboxtag, CPoint now, ObjectType objecttype);
	bool moviable(std::vector<std::vector<Object>> data, CPoint now, int move, int height, int width);
	CPoint bobmove(CPoint bob, int move);
	CPoint return_move(int movetag);
	CPoint ReturnOri(int level);
};
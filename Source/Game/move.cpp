#include "stdafx.h"
# include "move.h"
# include "Object.h"
# include <fstream>
# include <string>
CPoint Move::bobmove(CPoint bob, int movetag) {
	CPoint move = return_move(movetag);
	
	bob.x += move.x;
	bob.y += move.y;

	return bob;
}

std::vector<std::vector<Object>> Move::movenobox(std::vector<std::vector<Object>> data,int level, int movetag, CPoint bob) {
	CPoint move = return_move(movetag);

	ori = ReturnOri(level);

	if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() != PassibleBlock)
		return data;

	Object temp;
	temp = data[bob.x][bob.y];
	data[bob.x][bob.y] = data[bob.x + move.x][bob.y + move.y];
	data[bob.x + move.x][bob.y + move.y] = temp;
	bob.x += move.x;
	bob.y += move.y;

	data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);

	return data;
}

std::vector<std::vector<Object>> Move::moveSbox(std::vector<std::vector<Object>> data, int level, int movetype, CPoint bob) {

	CPoint move = return_move(movetype);

	if (data[bob.x + 2 * move.x][bob.y + 2 * move.y].ReturnObjectType() == Hole) {
		data[bob.x + 2 * move.x][bob.y + 2 * move.y].changeObjecttype(PassibleBlock);
		data[bob.x + move.x][bob.y + move.y].changeObjecttype(PassibleBlock);
	}

	ori = ReturnOri(level);
	Object temp;
	temp = data[bob.x][bob.y];
	data[bob.x][bob.y] = data[bob.x + 2 * move.x][bob.y + 2 * move.y];
	data[bob.x + 2 * move.x][bob.y + 2 * move.y] = data[bob.x + move.x][bob.y + move.y];
	data[bob.x + move.x][bob.y + move.y] = temp;
	bob.x += move.x;
	bob.y += move.y;

	data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
	data[bob.x + move.x][bob.y + move.y].SetImage(CPoint(bob.x + move.x, bob.y + move.y), ori);
	
	return data;
}

std::vector<std::vector<Object>> Move::moveMbox(std::vector<std::vector<Object>> data, int level, int movetype, int mboxtag, CPoint bob) {
	CPoint move = return_move(movetype);
	ori = ReturnOri(level);
	Object temp;
	if (movetype == 0 || movetype == 1) {
		temp = data[mboxtag][bob.y + 2 * move.y];
		data[mboxtag][bob.y + 2 * move.y] = data[mboxtag][bob.y + move.y];
		data[mboxtag][bob.y + move.y] = temp;

		temp = data[mboxtag + 1][bob.y + 2 * move.y];
		data[mboxtag + 1][bob.y + 2 * move.y] = data[mboxtag + 1][bob.y + move.y];
		data[mboxtag + 1][bob.y + move.y] = temp;

		temp = data[bob.x][bob.y + move.y];
		data[bob.x][bob.y + move.y] = data[bob.x][bob.y];
		data[bob.x][bob.y] = temp;

		bob.x += move.x;
		bob.y += move.y;
		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		data[bob.x + move.x][bob.y + move.y].SetImage(CPoint(bob.x + move.x, bob.y + move.y), ori);
		data[mboxtag][bob.y].SetImage(CPoint(mboxtag, bob.y), ori);
		data[mboxtag + move.x][bob.y + move.y].SetImage(CPoint(mboxtag + move.x, bob.y + move.y), ori);
	}
	else {
		temp = data[bob.x + 3 * move.x][bob.y];
		data[bob.x + 3 * move.x][bob.y] = data[bob.x + 2 * move.x][bob.y];
		data[bob.x + 2 * move.x][bob.y] = temp;

		temp = data[bob.x + 2 * move.x][bob.y];
		data[bob.x + 2 * move.x][bob.y] = data[bob.x + move.x][bob.y];
		data[bob.x + move.x][bob.y] = temp;

		temp = data[bob.x + move.x][bob.y];
		data[bob.x + move.x][bob.y] = data[bob.x][bob.y];
		data[bob.x][bob.y] = temp;

		bob.x += move.x;
		bob.y += move.y;
		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		data[bob.x + move.x][bob.y].SetImage(CPoint(bob.x + move.x, bob.y), ori);
		data[bob.x - move.x][bob.y].SetImage(CPoint(bob.x - move.x, bob.y), ori);
		data[bob.x + 2 * move.x][bob.y].SetImage(CPoint(bob.x + 2 * move.x, bob.y), ori);
	}
	return data;
}

CPoint Move::return_move(int movetag) {
	CPoint move = (0, 0);
	switch (movetag) {
	case 0:	// up
		move.y = -1;
		break;
	case 1:	// down
		move.y = 1;
		break;
	case 2:	// left
		move.x = -1;
		break;
	case 3:	// right
		move.x = 1;
		break;
	}
	return move;
}

CPoint Move::ReturnOri(int level) {
	std::string filename = "Resources/map" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);

	CPoint ori;
	ifs >> ori.x;
	ifs >> ori.y;

	ifs.close();

	return ori;
}

bool Move::moviable(std::vector<std::vector<Object>> data, CPoint now, int movetype, int height, int width) {
	CPoint move = return_move(movetype);
	switch (movetype) {
	case 0:
		if (now.y - 1 < 0 || data[now.x][now.y - 1].ReturnObjectType() == ImpassibleBlock) {
			return FALSE;
		}
		else if (now.y - 1 >= 0 && (data[now.x][now.y - 1].ReturnObjectType() == PassibleBlock || data[now.x][now.y - 1].ReturnObjectType() == Hole)) {
			return TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x, now.y - 1), movetype, height, width);
		}
		break;
	case 1:
		if (now.y + 1 >= height || data[now.x][now.y + 1].ReturnObjectType() == ImpassibleBlock) {
			return FALSE;
		}
		else if (now.y + 1 < height && (data[now.x][now.y + 1].ReturnObjectType() == PassibleBlock || data[now.x][now.y - 1].ReturnObjectType() == Hole)) {
			return TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x, now.y + 1), movetype, height, width);
		}
		break;
	case 2:
		if (now.x - 1 < 0 || data[now.x - 1][now.y].ReturnObjectType() == ImpassibleBlock) {
			return FALSE;
		}
		else if (now.x - 1 >= 0 && (data[now.x - 1][now.y].ReturnObjectType() == PassibleBlock || data[now.x - 1][now.y].ReturnObjectType() == Hole)) {
			return TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x - 1, now.y), movetype, height, width);
		}
		break;
	case 3:
		if (now.x + 1 >= width || data[now.x + 1][now.y].ReturnObjectType() == ImpassibleBlock) {
			return FALSE;
		}
		else if (now.x + 1 < width && (data[now.x + 1][now.y].ReturnObjectType() == PassibleBlock || data[now.x + 1][now.y].ReturnObjectType() == Hole)) {
			return TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x + 1, now.y ), movetype, height, width);
		}
	default:
		break;
	}
}
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

	if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() == PassibleBlock) {
		
		data[bob.x][bob.y].SetObject(PassibleBlock);
		data[bob.x + move.x][bob.y + move.y].SetObject(Character);

		bob.x += move.x;
		bob.y += move.y;

		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);

	}
	
	return data;
}

std::vector<std::vector<Object>> Move::moveSbox(std::vector<std::vector<Object>> data, int level, int movetype, CPoint bob, ObjectType objecttype) {
	CPoint move = return_move(movetype);

	bool hole = true;
	if (data[bob.x + 2 * move.x][bob.y + 2 * move.y].ReturnObjectType() == Hole) {
		data[bob.x + 2 * move.x][bob.y + 2 * move.y].SetObject(PassibleBlock);
		data[bob.x + move.x][bob.y + move.y].SetObject(PassibleBlock);
		hole = false;
	}

	int box_sum = 0;
	for (int i = 1; i < 10; i++) {
		if (data[bob.x + i * move.x][bob.y + i * move.y].ReturnObjectType() == Sbox) {
			box_sum += 1;
		}
		else {
			break;
		}
	}
	ori = ReturnOri(level);

	data[bob.x][bob.y].SetObject(PassibleBlock);
	data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);

	

	if (objecttype == Character) {
		bob.x += move.x;
		bob.y += move.y;
		data[bob.x][bob.y].SetObject(Character);
		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
	}
	else if(objecttype == Mbox){
		data[bob.x][bob.y].SetObject(Mbox);
		if (data[bob.x - 1][bob.y].ReturnObjectType() == Mbox) {
			data[bob.x - 1][bob.y].setbox = true;
			data[bob.x - 1][bob.y].SetObject(Mbox);
			data[bob.x - 1][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		}
		else {
			data[bob.x + 1][bob.y].SetObject(Mbox);
			data[bob.x][bob.y].setbox = true;
			data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		}
	}

	
	
	if (box_sum > 1) {
		for (int i = 1; i <= box_sum; i++) {
			data[bob.x + i * move.x][bob.y + i * move.y].SetObject(Sbox);
			data[bob.x + i * move.x][bob.y + i * move.y].SetImage(CPoint(bob.x + i * move.x, bob.y + i * move.y), ori);
		}
	}
	else if(hole) {
		data[bob.x + move.x][bob.y + move.y].SetObject(Sbox);
		data[bob.x + move.x][bob.y + move.y].SetImage(CPoint(bob.x + move.x, bob.y + move.y), ori);
	}
	return data;
}

std::vector<std::vector<Object>> Move::moveMbox(std::vector<std::vector<Object>> data, int level, int movetype, int mboxtag, CPoint now, ObjectType objecttype) {
	CPoint move = return_move(movetype);
	ori = ReturnOri(level);

	data[now.x][now.y].SetObject(PassibleBlock);
	data[now.x][now.y].SetImage(CPoint(mboxtag, now.y), ori);
	data[mboxtag][now.y + move.y].SetObject(PassibleBlock);
	data[mboxtag][now.y + move.y].SetImage(CPoint(mboxtag, now.y + move.y), ori);
	data[mboxtag + 1][now.y + move.y].SetObject(PassibleBlock);
	data[mboxtag + 1][now.y + move.y].SetImage(CPoint(mboxtag + 1, now.y + move.y), ori);
	
	now.x += move.x;
	now.y += move.y;

	data[now.x][now.y].SetObject(objecttype);
	data[now.x][now.y].SetImage(CPoint(now.x, now.y), ori);


	data[mboxtag + move.x][now.y + move.y].SetObject(Mbox);
	data[mboxtag + move.x][now.y + move.y].setbox = true;
	data[mboxtag + move.x][now.y + move.y].SetImage(CPoint(mboxtag + move.x, now.y + move.y), ori);
	data[mboxtag + move.x + 1][now.y + move.y].SetObject(Mbox);
	data[mboxtag + move.x + 1][now.y + move.y].setbox = false;
	data[mboxtag + move.x + 1][now.y + move.y].SetImage(CPoint(mboxtag + move.x + 1, now.y + move.y), ori);



	return data;
}


std::vector<std::vector<Object>> Move::moveMSbox(std::vector<std::vector<Object>> data, int level, int movetype, int mboxtag, CPoint now, ObjectType objecttype) {
	CPoint move = return_move(movetype);
	ori = ReturnOri(level);

	
	
	if (movetype == 0 || movetype == 1) {
		if (data[mboxtag][now.y + 2 * move.y].ReturnObjectType() == Sbox) {
			data[mboxtag][now.y + 3 * move.y].SetObject(Sbox);
			data[mboxtag][now.y + 3 * move.y].SetImage(CPoint(mboxtag, now.y + 3 * move.y), ori);
		}
		else if (data[mboxtag + 1][now.y + 2 * move.y].ReturnObjectType() == Sbox) {
			data[mboxtag + 1][now.y + 3 * move.y].SetObject(Sbox);
			data[mboxtag + 1][now.y + 3 * move.y].SetImage(CPoint(mboxtag + 1, now.y + 3 * move.y), ori);
		}
		else {
			return data;
		}


		data[mboxtag][now.y + 2 * move.y].SetObject(Mbox);
		data[mboxtag][now.y + 2 * move.y].SetImage(CPoint(mboxtag, now.y + 2 * move.y), ori);
		data[mboxtag + 1][now.y + 2 * move.y].SetObject(Mbox);
		data[mboxtag][now.y + 2 * move.y].SetImage(CPoint(mboxtag + 1, now.y + 2 * move.y), ori);

		data[mboxtag][now.y + move.y].SetObject(PassibleBlock);
		data[mboxtag][now.y + move.y].SetImage(CPoint(mboxtag + 1, now.y + move.y), ori);
		data[mboxtag + 1][now.y + move.y].SetObject(PassibleBlock);
		data[mboxtag + 1][now.y + move.y].SetImage(CPoint(mboxtag + 1, now.y + move.y), ori);
		
	}
	else {
		if (data[now.x + 3 * move.x][now.y].ReturnObjectType() == Sbox) {
			data[now.x + 4 * move.x][now.y].SetObject(Sbox);
			data[now.x + 4 * move.x][now.y].SetImage(CPoint(now.x + 4 * move.x, now.y), ori);
		}
		else {
			return data;
		}


		data[mboxtag + move.x][now.y].SetObject(Mbox);
		data[mboxtag + move.x][now.y].SetImage(CPoint(mboxtag + move.x, now.y), ori);
		data[mboxtag + 1 + move.x][now.y].SetObject(Mbox);
		data[mboxtag + 1 + move.x][now.y].SetImage(CPoint(mboxtag + 2 * move.x, now.y), ori);
	}

	data[now.x][now.y].SetObject(PassibleBlock);
	data[now.x][now.y].SetImage(CPoint(mboxtag, now.y), ori);

	now.x += move.x;
	now.y += move.y;

	data[now.x][now.y].SetObject(objecttype);
	data[now.x][now.y].SetImage(CPoint(now.x, now.y), ori);

	return data;
}

std::vector<std::vector<Object>> Move::moveLbox(std::vector<std::vector<Object>> data, int level, int movetype, CPoint lboxtag, CPoint now, ObjectType objecttype) {
	CPoint move = return_move(movetype);
	ori = ReturnOri(level);

	
	switch (movetype) {
	case 0:
		data[lboxtag.x][lboxtag.y + 1].SetObject(PassibleBlock);
		data[lboxtag.x][lboxtag.y + 1].SetImage(CPoint(lboxtag.x, lboxtag.y + 1), ori);
		data[lboxtag.x + 1][lboxtag.y + 1].SetObject(PassibleBlock);
		data[lboxtag.x + 1][lboxtag.y + 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 1), ori);

		if (data[lboxtag.x][lboxtag.y - 1].ReturnObjectType() == Sbox) {
			data[lboxtag.x][lboxtag.y - 2].SetObject(Sbox);
			data[lboxtag.x][lboxtag.y - 2].SetImage(CPoint(lboxtag.x, lboxtag.y - 2), ori);
			data[lboxtag.x][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y - 1].SetImage(CPoint(lboxtag.x, lboxtag.y - 1), ori);
		}
		if (data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Sbox) {
			data[lboxtag.x + 1][lboxtag.y - 2].SetObject(Sbox);
			data[lboxtag.x + 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}

		if (data[lboxtag.x][lboxtag.y - 1].ReturnObjectType() == Mbox && data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x][lboxtag.y - 2].setbox = true;
			data[lboxtag.x][lboxtag.y - 2].SetImage(CPoint(lboxtag.x, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y - 1].SetImage(CPoint(lboxtag.x, lboxtag.y - 1), ori);
			data[lboxtag.x + 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}
		else if(data[lboxtag.x][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x][lboxtag.y - 2].setbox = false;
			data[lboxtag.x][lboxtag.y - 2].SetImage(CPoint(lboxtag.x, lboxtag.y - 2), ori);
			data[lboxtag.x - 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x - 1][lboxtag.y - 2].setbox = true;
			data[lboxtag.x - 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x - 1, lboxtag.y - 2), ori);
			data[lboxtag.x][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y - 1].SetImage(CPoint(lboxtag.x, lboxtag.y - 1), ori);
			data[lboxtag.x - 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x - 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x - 1, lboxtag.y - 1), ori);
		}
		else if (data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x + 2][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 2][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 2][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x + 2][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 1), ori);
			data[lboxtag.x + 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}

		break;
	case 1:
		data[lboxtag.x][lboxtag.y].SetObject(PassibleBlock);
		data[lboxtag.x][lboxtag.y].SetImage(CPoint(lboxtag.x, lboxtag.y), ori);
		data[lboxtag.x + 1][lboxtag.y].SetObject(PassibleBlock);
		data[lboxtag.x + 1][lboxtag.y].SetImage(CPoint(lboxtag.x + 1, lboxtag.y), ori);

		if (data[lboxtag.x][lboxtag.y + 2].ReturnObjectType() == Sbox) {
			data[lboxtag.x][lboxtag.y + 3].SetObject(Sbox);
			data[lboxtag.x][lboxtag.y + 3].SetImage(CPoint(lboxtag.x, lboxtag.y + 3), ori);
			data[lboxtag.x][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y + 2].SetImage(CPoint(lboxtag.x, lboxtag.y + 2), ori);
		}
		if (data[lboxtag.x + 1][lboxtag.y + 2].ReturnObjectType() == Sbox) {
			data[lboxtag.x + 1][lboxtag.y + 3].SetObject(Sbox);
			data[lboxtag.x + 1][lboxtag.y + 3].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 3), ori);
			data[lboxtag.x + 1][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y + 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 2), ori);
		}

		if (data[lboxtag.x][lboxtag.y + 2].ReturnObjectType() == Mbox && data[lboxtag.x + 1][lboxtag.y + 2].ReturnObjectType() == Mbox) {
			data[lboxtag.x][lboxtag.y + 3].SetObject(Mbox);
			data[lboxtag.x][lboxtag.y + 3].setbox = true;
			data[lboxtag.x][lboxtag.y + 3].SetImage(CPoint(lboxtag.x, lboxtag.y + 3), ori);
			data[lboxtag.x + 1][lboxtag.y + 3].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y + 3].setbox = false;
			data[lboxtag.x + 1][lboxtag.y + 3].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 3), ori);
			data[lboxtag.x][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y + 2].SetImage(CPoint(lboxtag.x, lboxtag.y + 2), ori);
			data[lboxtag.x + 1][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y + 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 2), ori);
		}
		else if(data[lboxtag.x + 1][lboxtag.y + 2].ReturnObjectType() == Mbox) {
			data[lboxtag.x + 2][lboxtag.y + 3].SetObject(Mbox);
			data[lboxtag.x + 2][lboxtag.y + 3].setbox = false;
			data[lboxtag.x + 2][lboxtag.y + 3].SetImage(CPoint(lboxtag.x + 2, lboxtag.y + 3), ori);
			data[lboxtag.x + 1][lboxtag.y + 3].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y + 3].setbox = true;
			data[lboxtag.x + 1][lboxtag.y + 3].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 3), ori);
			data[lboxtag.x + 2][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y + 2].SetImage(CPoint(lboxtag.x + 2, lboxtag.y + 2), ori);
			data[lboxtag.x + 1][lboxtag.y + 2].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y + 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 2), ori);
		}
		else if (data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x + 2][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 2][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 2][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x + 2][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 1), ori);
			data[lboxtag.x + 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}
		break;
	case 2:
		data[lboxtag.x + 1][lboxtag.y].SetObject(PassibleBlock);
		data[lboxtag.x + 1][lboxtag.y].SetImage(CPoint(lboxtag.x + 1, lboxtag.y), ori);
		data[lboxtag.x + 1][lboxtag.y + 1].SetObject(PassibleBlock);
		data[lboxtag.x + 1][lboxtag.y + 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y + 1), ori);

		if (data[lboxtag.x - 1][lboxtag.y].ReturnObjectType() == Sbox) {
			data[lboxtag.x - 2][lboxtag.y].SetObject(Sbox);
			data[lboxtag.x - 2][lboxtag.y].SetImage(CPoint(lboxtag.x - 2, lboxtag.y), ori);
			data[lboxtag.x - 1][lboxtag.y].SetObject(PassibleBlock);
			data[lboxtag.x - 1][lboxtag.y].SetImage(CPoint(lboxtag.x - 1, lboxtag.y), ori);
		}
		else if (data[lboxtag.x - 1][lboxtag.y + 1].ReturnObjectType() == Sbox) {
			data[lboxtag.x - 2][lboxtag.y + 1].SetObject(Sbox);
			data[lboxtag.x - 2][lboxtag.y + 1].SetImage(CPoint(lboxtag.x - 2, lboxtag.y + 1), ori);
			data[lboxtag.x - 1][lboxtag.y + 1].SetObject(PassibleBlock);
			data[lboxtag.x - 1][lboxtag.y + 1].SetImage(CPoint(lboxtag.x - 1, lboxtag.y + 1), ori);
		}

		if (data[lboxtag.x][lboxtag.y].ReturnObjectType() == Mbox && data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x][lboxtag.y].SetObject(Mbox);
			data[lboxtag.x][lboxtag.y].setbox = true;
			data[lboxtag.x][lboxtag.y].SetImage(CPoint(lboxtag.x, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y].setbox = false;
			data[lboxtag.x + 1][lboxtag.y].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x][lboxtag.y].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y].SetImage(CPoint(lboxtag.x, lboxtag.y - 1), ori);
			data[lboxtag.x + 1][lboxtag.y].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}
		else if (data[lboxtag.x][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x][lboxtag.y - 2].setbox = false;
			data[lboxtag.x][lboxtag.y - 2].SetImage(CPoint(lboxtag.x, lboxtag.y - 2), ori);
			data[lboxtag.x - 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x - 1][lboxtag.y - 2].setbox = true;
			data[lboxtag.x - 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x - 1, lboxtag.y - 2), ori);
			data[lboxtag.x][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x][lboxtag.y - 1].SetImage(CPoint(lboxtag.x, lboxtag.y - 1), ori);
			data[lboxtag.x - 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x - 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x - 1, lboxtag.y - 1), ori);
		}
		else if (data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
			data[lboxtag.x + 2][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 2][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 2][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 2), ori);
			data[lboxtag.x + 1][lboxtag.y - 2].SetObject(Mbox);
			data[lboxtag.x + 1][lboxtag.y - 2].setbox = false;
			data[lboxtag.x + 1][lboxtag.y - 2].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 2), ori);
			data[lboxtag.x + 2][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 2, lboxtag.y - 1), ori);
			data[lboxtag.x + 1][lboxtag.y - 1].SetObject(PassibleBlock);
			data[lboxtag.x + 1][lboxtag.y - 1].SetImage(CPoint(lboxtag.x + 1, lboxtag.y - 1), ori);
		}
		break;
	case 3:
		data[lboxtag.x][lboxtag.y].SetObject(PassibleBlock);
		data[lboxtag.x][lboxtag.y].SetImage(CPoint(lboxtag.x, lboxtag.y), ori);
		data[lboxtag.x][lboxtag.y + 1].SetObject(PassibleBlock);
		data[lboxtag.x][lboxtag.y + 1].SetImage(CPoint(lboxtag.x, lboxtag.y + 1), ori);

		if (data[lboxtag.x + 2][lboxtag.y].ReturnObjectType() == Sbox) {
			data[lboxtag.x + 3][lboxtag.y].SetObject(Sbox);
			data[lboxtag.x + 3][lboxtag.y].SetImage(CPoint(lboxtag.x + 3, lboxtag.y), ori);
			data[lboxtag.x + 2][lboxtag.y].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y].SetImage(CPoint(lboxtag.x + 2, lboxtag.y), ori);
		}
		else if (data[lboxtag.x + 2][lboxtag.y + 1].ReturnObjectType() == Sbox) {
			data[lboxtag.x + 3][lboxtag.y + 1].SetObject(Sbox);
			data[lboxtag.x + 3][lboxtag.y + 1].SetImage(CPoint(lboxtag.x + 3, lboxtag.y + 1), ori);
			data[lboxtag.x + 2][lboxtag.y + 1].SetObject(PassibleBlock);
			data[lboxtag.x + 2][lboxtag.y + 1].SetImage(CPoint(lboxtag.x + 2, lboxtag.y + 1), ori);
		}
		break;
	default:
		break;
	}
	data[now.x][now.y].SetObject(PassibleBlock);
	data[now.x][now.y].SetImage(CPoint(now.x, now.y), ori);
	data[lboxtag.x + move.x][lboxtag.y + move.y].SetObject(Lbox);
	data[lboxtag.x + move.x][lboxtag.y + move.y].SetImage(CPoint(lboxtag.x + move.x, lboxtag.y + move.y), ori);
	data[lboxtag.x + move.x][lboxtag.y + move.y].setbox = true;
	data[lboxtag.x + move.x][lboxtag.y + 1 + move.y].SetObject(Lbox);
	data[lboxtag.x + move.x][lboxtag.y + 1 + move.y].SetImage(CPoint(lboxtag.x + move.x, lboxtag.y + 1 + move.y), ori);
	data[lboxtag.x + move.x][lboxtag.y + 1 + move.y].setbox = false;
	data[lboxtag.x + 1 + move.x][lboxtag.y + move.y].SetObject(Lbox);
	data[lboxtag.x + 1 + move.x][lboxtag.y + move.y].SetImage(CPoint(lboxtag.x + 1 + move.x, lboxtag.y + move.y), ori);
	data[lboxtag.x + 1 + move.x][lboxtag.y + move.y].setbox = false;
	data[lboxtag.x + 1 + move.x][lboxtag.y + 1 + move.y].SetObject(Lbox);
	data[lboxtag.x + 1 + move.x][lboxtag.y + 1 + move.y].SetImage(CPoint(lboxtag.x + 1 + move.x, lboxtag.y + 1 + move.y), ori);
	data[lboxtag.x + 1 + move.x][lboxtag.y + 1 + move.y].setbox = false;



	now.x += move.x;
	now.y += move.y;

	data[now.x][now.y].SetObject(objecttype);
	data[now.x][now.y].SetImage(CPoint(now.x, now.y), ori);


	
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
	bool tag;
	switch (movetype) {
	case 0:
		if (now.y - 1 < 0 || data[now.x][now.y - 1].ReturnObjectType() == ImpassibleBlock) {
			tag = FALSE;
		}
		else if (now.y - 1 >= 0 && (data[now.x][now.y - 1].ReturnObjectType() == PassibleBlock || data[now.x][now.y - 1].ReturnObjectType() == Hole)) {
			tag = TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x, now.y - 1), movetype, height, width);
		}
		break;
	case 1:
		if (now.y + 1 >= height || data[now.x][now.y + 1].ReturnObjectType() == ImpassibleBlock) {
			tag = FALSE;
		}
		else if (now.y + 1 < height && (data[now.x][now.y + 1].ReturnObjectType() == PassibleBlock || data[now.x][now.y + 1].ReturnObjectType() == Hole)) {
			tag = TRUE;
		}
		else {
			return  Move::moviable(data, CPoint(now.x, now.y + 1), movetype, height, width);
		}
		break;
	case 2:
		if (now.x - 1 < 0 || data[now.x - 1][now.y].ReturnObjectType() == ImpassibleBlock) {
			tag = FALSE;
		}
		else if (now.x - 1 >= 0 && (data[now.x - 1][now.y].ReturnObjectType() == PassibleBlock || data[now.x - 1][now.y].ReturnObjectType() == Hole)) {
			tag = TRUE;
		}
		else {
			tag = Move::moviable(data, CPoint(now.x - 1, now.y), movetype, height, width);
		}
		break;
	case 3:
		if (now.x + 1 >= width || data[now.x + 1][now.y].ReturnObjectType() == ImpassibleBlock) {
			tag = FALSE;
		}
		else if (now.x + 1 < width && (data[now.x + 1][now.y].ReturnObjectType() == PassibleBlock || data[now.x + 1][now.y].ReturnObjectType() == Hole)) {
			tag = TRUE;
		}
		else {
			tag = Move::moviable(data, CPoint(now.x + 1, now.y ), movetype, height, width);
		}
	default:
		break;
	}

	return tag;
}
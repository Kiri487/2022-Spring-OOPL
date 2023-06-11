#include "stdafx.h"
#include "map.h"
#include <fstream>
#include <string>


void Map::Matrix(int level) {
	objectlist.ObjectList();
	std::string filename = "Resources/map" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);
	
	CPoint ori, mapsize;
	ifs >> ori.x;
	ifs >> ori.y;
	ifs >> mapsize.x;
	ifs >> mapsize.y;

	for (int i = 0; i <= width; i++) {
		data[i].clear();
	}
	data.clear();
	this->width = mapsize.x;
	this->height = mapsize.y;
	for (int i = 0; i <= width; i++) {
		data.push_back(std::vector<Object>(height));
	}

	for (int i = 0; i < mapsize.y; i++) {
		int num;
		for (int j = 0; j < mapsize.x; j++) {
			ifs >> num;
			ObjectType objtyp;
			objtyp = static_cast<ObjectType>(num);
			data[j][i].LoadObjectImage(objtyp, CPoint(j, i), ori);
			data[j][i].ObjectList();
			switch (objtyp)
			{
			case Character:
				bob.x = j;
				bob.y = i;
				break;
			case Sbox :
				data[j][i].setbox = TRUE;
				break;
			case Mbox:
				data[j][i].setbox = TRUE;
				if (j > 0 && data[j - 1][i].setbox == TRUE && data[j - 1][i].ReturnObjectType() == Mbox)
					data[j][i].setbox = FALSE;
				break;
			case Lbox:
				data[j][i].setbox = TRUE;
				if (j > 0 && data[j - 1][i].setbox == TRUE && data[j - 1][i].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				else if (i > 0 && data[j][i - 1].setbox == TRUE && data[j][i - 1].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				else if (i > 0 && j > 0 && data[j - 1][i - 1].setbox == TRUE && data[j - 1][i - 1].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				break;
			default:
				data[j][i].setbox = FALSE;
				break;
			}
			
		}
	}

	ifs.close();

	MapStep.push(data);
	//MapStep.push(GetNowMap());
	BobStep.push(bob);

	filename = "Resources/other_object" + std::to_string(level) + ".txt";
	ifs.open(filename);

	int temp_x, temp_y;
	ifs >> temp_x;
	ifs >> temp_y;

	this->width = mapsize.x;
	this->height = mapsize.y;

	status_data.clear();
	status_data.resize(mapsize.x, std::vector<int>(mapsize.y));

	for (int i = 0; i < mapsize.y; i++) {
		for (int j = 0; j < mapsize.x; j++) {
			ifs >> status_data[j][i];
		}
	}

	ifs.close();
}



void Map::Show() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			data[i][j].ShowObjectImage();
		}
	}
}


bool Map::boundary(CPoint target, int movetag) {
	bool tag = true;
	switch(movetag){
	case 0:	// up
		if (target.y < 0)
			tag = false;
		break;
	case 1:	// down
		if (target.y > height)
			tag = false;
		break;
	case 2:	// left
		if (target.x < 0)
			tag = false;
		break;
	case 3:	// right
		if (target.x > width)
			tag = false;
		break;
	}
	return tag;
}


CPoint Map::boxtag(CPoint target, ObjectType boxtype) {
	CPoint boxtag = target;
	switch (boxtype)
	{
	case Mbox:
		if (data[target.x - 1][target.y].ReturnObjectType() == Mbox) {
			boxtag.x = target.x - 1; // character on box right
		}	
		else {
			boxtag.x = target.x; // character on box left
		}
		break;
	case Lbox:
		if (target.x + 1 < width && target.y - 1 >= 0 && target.y + 1 < height && target.y - 1 >= 0) {
			if (data[target.x + 1][target.y].ReturnObjectType() == Lbox && data[target.x + 1][target.y + 1].ReturnObjectType() == Lbox && data[target.x][target.y + 1].ReturnObjectType() == Lbox) {
				boxtag = target;
			}
			else if (data[target.x - 1][target.y].ReturnObjectType() == Lbox && data[target.x - 1][target.y + 1].ReturnObjectType() == Lbox && data[target.x][target.y + 1].ReturnObjectType() == Lbox) {
				boxtag.x = target.x - 1;
			}
			else if (data[target.x + 1][target.y].ReturnObjectType() == Lbox && data[target.x + 1][target.y - 1].ReturnObjectType() == Lbox && data[target.x][target.y - 1].ReturnObjectType() == Lbox) {
				boxtag.y = target.y - 1;
			}
			else {
				boxtag.x = target.x - 1;
				boxtag.y = target.y - 1;
			}
		}
		break;
	default:
		break;
	}
	
	
	return boxtag;
}



void Map::MoveObject(int level, int movetype) {
	CPoint move = CPoint(0, 0);
	switch (movetype) {
	case 0: // up
		move.y = -1;
		break;
	case 1: // down
		move.y = 1;
		break;

	case 2: // left
		move.x = -1;
		break;

	case 3: // right
		move.x = 1;
		break;
	default:
		break;
	}
	CPoint ori_bob = bob;
	if (movestep.moviable(data, bob, movetype, height, width)) {
		if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() == PassibleBlock) {
			data = movestep.movenobox(data, level, movetype, bob);
			bob = movestep.bobmove(bob, movetype);
		}
		else if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() == Sbox) {
			bool SMbox = true;
			if (data[bob.x + 2 * move.x][bob.y + 2 * move.y].ReturnObjectType() == Mbox) {
				CPoint mboxtag = boxtag(CPoint(bob.x + 2 * move.x, bob.y + 2 * move.y), Mbox);
				if (movestep.moviable(data, CPoint(mboxtag.x, bob.y + move.y), movetype, height, width) && movestep.moviable(data, CPoint(mboxtag.x + 1, bob.y + move.y), movetype, height, width)) {
					data = movestep.moveMbox(data, level, movetype, mboxtag, CPoint(bob.x + move.x, bob.y + move.y));
				}
				else {
					SMbox = false;
				}
				
			}
			else if (data[bob.x + 2 * move.x][bob.y + 2 * move.y].ReturnObjectType() == Lbox) {
				CPoint lboxtag = boxtag(CPoint(bob.x + 2 * move.x, bob.y + 2 * move.y), Lbox);
				if (movestep.moviable(data, CPoint(lboxtag.x, lboxtag.y), movetype, height, width) &&
					movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y), movetype, height, width) &&
					movestep.moviable(data, CPoint(lboxtag.x, lboxtag.y + 1), movetype, height, width) &&
					movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y + 1), movetype, height, width)) {
					data = movestep.moveLbox(data, level, movetype, lboxtag, CPoint(bob.x + move.x, bob.y + move.y), Character);
				}
				else {
					SMbox = false;
				}
			}
			if (SMbox) {
				data = movestep.moveSbox(data, level, movetype, bob, Character);
				bob = movestep.bobmove(bob, movetype);
			}
			
		}
		else if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() == Mbox) {
			CPoint mboxtag = boxtag(CPoint(bob.x + move.x, bob.y + move.y), Mbox);
			
			if (movestep.moviable(data, CPoint(mboxtag.x, bob.y), movetype, height, width) && movestep.moviable(data, CPoint(mboxtag.x + 1, bob.y), movetype, height, width)) {
				
				if (level == 6) {
					data = movestep.moveMSbox(data, level, movetype, mboxtag.x, bob, Character);
					if (mboxtag.x == 2 && mboxtag.y == 2 && bob.x + move.x == mboxtag.x && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else if (mboxtag.x + 1 == 2 && mboxtag.y == 2 && bob.x + move.x == mboxtag.x + 1 && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
						bob = movestep.bobmove(bob, movetype);
					}
				}
				else if (level == 11) {
					if (data[mboxtag.x + move.x][mboxtag.y + move.y].ReturnObjectType() == Sbox) {
						data = movestep.moveSbox(data, level, movetype, mboxtag, PassibleBlock);
					}
					if (mboxtag.x == 4 && mboxtag.y == 1 && bob.x + move.x == mboxtag.x && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else if (mboxtag.x + 1 == 4 && mboxtag.y == 1 && bob.x + move.x == mboxtag.x + 1 && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else if (mboxtag.x == 5 && mboxtag.y == 3 && bob.x + move.x == mboxtag.x && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else if (mboxtag.x + 1 == 5 && mboxtag.y == 3 && bob.x + move.x == mboxtag.x + 1 && bob.y + move.y == mboxtag.y) {
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					}
					else {
						data = movestep.moveMSbox(data, level, movetype, mboxtag.x, bob, Character);
						data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
						bob = movestep.bobmove(bob, movetype);
					}
				}
				else {
					if (data[mboxtag.x + move.x][mboxtag.y + move.y].ReturnObjectType() == Lbox) {
						CPoint lboxtag = boxtag(CPoint(mboxtag.x + move.x, mboxtag.y + move.y), Lbox);
						if (movestep.moviable(data, lboxtag, movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y), movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x, lboxtag.y + 1), movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y + 1), movetype, height, width)) {
							data = movestep.moveLbox(data, level, movetype, lboxtag, CPoint(mboxtag.x, mboxtag.y), PassibleBlock);
						}
						else {
							return;
						}
					}
					else if (data[mboxtag.x + 1 + move.x][mboxtag.y + move.y].ReturnObjectType() == Lbox) {
						CPoint lboxtag = boxtag(CPoint(mboxtag.x + 1 + move.x, mboxtag.y + move.y), Lbox);
						if (movestep.moviable(data, lboxtag, movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y), movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x, lboxtag.y + 1), movetype, height, width) &&
							movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y + 1), movetype, height, width)) {
							data = movestep.moveLbox(data, level, movetype, lboxtag, CPoint(mboxtag.x + 1, mboxtag.y), PassibleBlock);
						}
						else {
							return;
						}
					}
					data = movestep.moveMSbox(data, level, movetype, mboxtag.x, bob, Character);
					data = movestep.moveMbox(data, level, movetype, mboxtag, bob);
					bob = movestep.bobmove(bob, movetype);
				}
				
			}
		}
		else if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() == Lbox) {
			CPoint lboxtag = boxtag(CPoint(bob.x + move.x, bob.y + move.y), Lbox);
			if (movestep.moviable(data, lboxtag, movetype, height, width) &&
				movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y), movetype, height, width) &&
				movestep.moviable(data, CPoint(lboxtag.x, lboxtag.y + 1), movetype, height, width) &&
				movestep.moviable(data, CPoint(lboxtag.x + 1, lboxtag.y + 1), movetype, height, width)) {
				if (movetype == 0) {
					if (data[lboxtag.x][lboxtag.y - 1].ReturnObjectType() == Mbox) {
						if (data[lboxtag.x - 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
							if (movestep.moviable(data, CPoint(lboxtag.x - 1, lboxtag.y - 1), movetype, height, width)) {
							}
							else {
								return;
							}
						}
					}
					else if(data[lboxtag.x + 1][lboxtag.y - 1].ReturnObjectType() == Mbox) {
						if (movestep.moviable(data, CPoint(lboxtag.x + 2, lboxtag.y - 1), movetype, height, width)) {
						}
						else {
							return;
						}
					}
				}
				else if (movetype == 1) {

				}
				
				data = movestep.moveLbox(data, level, movetype, lboxtag, bob, Character);
				bob = movestep.bobmove(bob, movetype);
			}

		}
	}

	if (ori_bob != bob) {
		MapStep.push(data);
		BobStep.push(bob);
	}
}


ObjectType Map::ReturnObjectType(int x, int y) {
	return data[x][y].ReturnObjectType();
}

string Map::PrintObjectType(int x, int y) {
	ObjectType objecttype = data[x][y].ReturnObjectType();
	string type;
	switch (objecttype) {
	case ImpassibleBlock:
		type = "0";
		break;
	case PassibleBlock:
		type = "1";
		break;
	case Character:
		type = "2";
		break;

	default:
		type = "x";
		break;
	}
	
	return type;
}

//std::vector<std::vector<Object>> Map::GetNowMap() {
//
//	std::vector<std::vector<Object>> now_map;
//
//	now_map.clear();
//	now_map.resize(width, std::vector<Object>(height));
//
//	now_map = data;
//
//	return now_map;
//}

void Map::Undo() {
	if (MapStep.size() != 1) {
		MapStep.pop();
		data = MapStep.top();
		BobStep.pop();
		bob = BobStep.top();
	}
}

void Map::MapStepClear() {
	while (!MapStep.empty()) {
		MapStep.pop();
		BobStep.pop();
	}
}

int Map::HoleTag(CPoint boxtag, ObjectType objecttype){
	switch (objecttype) {
	case Mbox:
		if (GetValue(boxtag.x, boxtag.y) == 2) {
			return 1;
		}
		else if (GetValue(boxtag.x + 1, boxtag.y) == 2) {
			return 2;
		}
		else {
			return 0;
		}
		break;
	default:
		return 3;
	}
	
}

int Map::GetValue(int x, int y) {
	return status_data[x][y];
}
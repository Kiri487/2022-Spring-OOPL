#pragma once

#include "../Library/gameutil.h"
#include<vector>

enum ObjectType {
	ImpassibleBlock,
	PassibleBlock,
	Character,
	Sbox,
	Mbox,
	Lbox,
	Hole
};

class Object {
private:
	ObjectType objecttype; 
	game_framework::CMovingBitmap image;
	
public:
	void ShowObjectImage();
	void LoadObjectImage(ObjectType objecttype, CPoint now, CPoint ori);
	ObjectType ReturnObjectType();
	void SetImage(CPoint now, CPoint ori);

	//Object operator=(const Object &other);

};
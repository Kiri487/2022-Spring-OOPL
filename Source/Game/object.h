#pragma once

#include "../Library/gameutil.h"

enum ObjectType {
	InpassibleBlock,
	PassibleBlock,
	Character,
	Sbox,
	Mbox,
	Lbox,
	Hole
};

class Object {
private:
	ObjectType objecttybe;
	game_framework::CMovingBitmap image;
	game_framework::CMovingBitmap charater;
	game_framework::CMovingBitmap sbox;
	game_framework::CMovingBitmap mbox;
	game_framework::CMovingBitmap lbox;

public:
	void ShowObjectImage();
	void LoadObjectImage(ObjectType objecttybe);
};
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

public:
	void ShowObjectImage();			
	
};
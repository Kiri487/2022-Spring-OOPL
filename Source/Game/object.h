#pragma once

#include "../Library/gameutil.h"
#include <vector>
#include <unordered_map>

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
	static bool standardObjectLoaded;
	static std::unordered_map<ObjectType, Object> StandardObject;
	
public:
	void ShowObjectImage();
	void LoadObjectImage(ObjectType objecttype, CPoint now, CPoint ori);
	ObjectType ReturnObjectType();
	void SetImage(CPoint now, CPoint ori);
	bool setbox;
	void SetObject(ObjectType new_object);
	void ObjectList();

	//Object operator=(const Object &other);

};
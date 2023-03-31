#include "stdafx.h"
#include "object.h"
#include "map.h"

void Object::ShowObjectImage() { 
}

void Object::LoadObjectImage(ObjectType objecttybe) {
	switch (objecttybe) {
		case Character:
			charater.LoadBitmapByString({ "resources/bob1.bmp", "resources/bob2.bmp", "resources/bob3.bmp"}, RGB(0, 0, 255));
			charater.SetTopLeft(1369, 25);
			charater.SetAnimation(165, false);
		case Sbox:
			charater.LoadBitmapByString({ "resources/sbox.bmp" }, RGB(0, 0, 255));
			charater.SetTopLeft(1369, 25);
		case Mbox:
		case Lbox:
	}
}

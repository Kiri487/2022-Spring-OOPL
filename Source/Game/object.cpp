#include "stdafx.h"
#include "object.h"
#include "map.h"

void Object::ShowObjectImage() {
	if (objecttype == Mbox) {
		if(setbox == TRUE)
			image.ShowBitmap();
	}
	else if (objecttype == Lbox) {
		if (setbox == TRUE)
			image.ShowBitmap();
	}
	else if (objecttype != ImpassibleBlock && objecttype != PassibleBlock) {
		image.ShowBitmap();
	}
}

void Object::LoadObjectImage(ObjectType objecttype, CPoint now, CPoint ori) {
	this->objecttype = objecttype;
	switch (objecttype) {
		case Character:
			image.LoadBitmapByString({ "resources/bob1.bmp", "resources/bob2.bmp", "resources/bob3.bmp"}, RGB(0, 0, 255));
			image.SetAnimation(165, false);
			break;
		case Sbox:
			image.LoadBitmapByString({ "resources/box_s.bmp" }, RGB(0, 0, 255));
			break;
		case Mbox:
			image.LoadBitmapByString({ "resources/box_m.bmp" }, RGB(0, 0, 255));
			break;
		case Lbox:
			image.LoadBitmapByString({ "resources/box_l.bmp" }, RGB(0, 0, 255));
			break;
		case Hole:
			image.LoadBitmapByString({ "resources/hole.bmp" }, RGB(0, 0, 255));
			break;
		default:
			break;
	}

	SetImage(now, ori);
	if (objecttype == Sbox || objecttype == Mbox || objecttype == Lbox && setbox == TRUE) {
		image.SetTopLeft(ori.x + 83 * now.x + 6, ori.y + 83 * now.y + 6);
	}
	
}



ObjectType Object::ReturnObjectType() {
	return objecttype;
}

void Object::SetImage(CPoint now, CPoint ori) {
	if (objecttype == Sbox || objecttype == Mbox || objecttype == Lbox && setbox == TRUE) {
		image.SetTopLeft(ori.x + 83 * now.x + 6, ori.y + 83 * now.y + 6);
	}
	if (objecttype == Hole) {
		image.SetTopLeft(ori.x + 83 * now.x + 6, ori.y + 83 * now.y + 6);
	}
	else if (objecttype == Character) {
		image.SetTopLeft(ori.x + 83 * now.x + 13, ori.y + 83 * now.y - 31);
	}
	else if (objecttype != ImpassibleBlock && objecttype != PassibleBlock) {
		image.SetTopLeft(ori.x + 83 * now.x, ori.y + 83 * now.y);
	}
}


#include "stdafx.h"
#include "../Library/gameutil.h"
//#include "../Library/gamecore.h"
#include "choose_level.h"
#include <string>

ChooseLevel::ChooseLevel() {

}

void ChooseLevel::Init() {
	background.LoadBitmapByString({ "resources/choose_background.bmp" });
	background.SetTopLeft(0, 0);
	button_x = 487;
	button_y = 272;
	state = false;

	//CDC *pDC = CDDraw::GetBackCDC();

	for (int i = 0; i < 18; i++) {
		if(i == 0 || i == 17) level_button[i].LoadBitmapByString({ "resources/story_button.bmp" });
		else level_button[i].LoadBitmapByString({ "resources/level_button.bmp" });

		if (i >= 0 && i <= 5) {
			level_button[i].SetTopLeft(button_x + i * 100, button_y);
			/*CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
			text_art.TextBorder(pDC, button_x + i * 100, button_y, 4, std::to_string(i));
			CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
			CTextDraw::Print(pDC, button_x + i * 100, button_y, std::to_string(i));*/
		}
		if (i >= 6 && i <= 11) {
			level_button[i].SetTopLeft(button_x + (i % 6) * 100, button_y + 100);
		}
		if (i >= 12 && i <= 17) {
			level_button[i].SetTopLeft(button_x + (i % 6) * 100, button_y + 200);
		}
	}

	//CDDraw::ReleaseBackCDC();
}

void ChooseLevel::Show() {

	background.ShowBitmap();

	for (int i = 0; i < 18; i++) {
		level_button[i].ShowBitmap();
	}
}

int ChooseLevel::press_level_button(CPoint point) {
	
	for (int i = 0; i <= 17; i++) {
		if (point.x >= level_button[i].GetLeft() && point.x <= level_button[i].GetLeft() + level_button[i].GetWidth() && point.y >= level_button[i].GetTop() && point.y <= level_button[i].GetTop() + level_button[i].GetHeight()) {
			return i;
		}
	}
	return -1;
}
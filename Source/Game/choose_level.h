#pragma once
using namespace game_framework;

class ChooseLevel {
public:
	ChooseLevel();
	void Init();
	void Show();
	void press_level_button(CPoint point);
private:
	CMovingBitmap background;
	CMovingBitmap level_button[18];
	int button_x;
	int button_y;
};
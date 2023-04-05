#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	test.Matrix(level);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	transition.LoadBitmapByString({
	"resources/transition1.bmp",
	"resources/transition2.bmp",
	"resources/transition3.bmp",
	"resources/transition4.bmp",
	"resources/transition5.bmp",
	"resources/transition6.bmp",
		}, RGB(0, 0, 255));
	transition.SetTopLeft(0, 0);
	transition.SetAnimation(70, true);
	transition.ToggleAnimation();

	background.LoadBitmapByString({
	"resources/1_background.bmp",
	"resources/2_background.bmp",
	"resources/3_background.bmp",
	"resources/4_background.bmp",
	"resources/5_background.bmp",
	"resources/6_background.bmp",
	"resources/7_background.bmp",
	"resources/8_background.bmp",
	"resources/9_background.bmp",
	"resources/10_background.bmp",
	"resources/11_background.bmp",
	"resources/12_background.bmp",
	"resources/13_background.bmp",
	"resources/14_background.bmp",
	"resources/15_background.bmp",
	"resources/16_background.bmp"
		});
	background.SetTopLeft(0, 0);

	music_icon.LoadBitmapByString({ "resources/music_on.bmp", "resources/music_off.bmp" });
	music_icon.SetTopLeft(1369, 25);

	sound_icon.LoadBitmapByString({ "resources/sound_on.bmp", "resources/sound_off.bmp" });
	sound_icon.SetTopLeft(1445, 25);

	exit_icon.LoadBitmapByString({ "resources/exit.bmp" });
	exit_icon.SetTopLeft(25, 25);

	choose_level.Init();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// enter
	if (nChar == VK_RETURN) {
		// !!! change level test !!! 
		level++; 
		if (level <= 16) {
			transition.ToggleAnimation();
		}
		// !!! change level test !!! 
	}
	else if (nChar == VK_UP) {
		for (int i = 0; i < test.width; i++) {
			for (int j = 0; j < test.height; j++) {
				test.MoveObject(level, i, j, 0);
			}
		}
	}
	else if (nChar == VK_DOWN) {
		for (int i = 0; i < test.width; i++) {
			for (int j = 0; j < test.height; j++) {
				test.MoveObject(level, i, j, 1);
			}
		}
	}
	else if (nChar == VK_LEFT) {
		for (int i = 0; i < test.width; i++) {
			for (int j = 0; j < test.height; j++) {
				test.MoveObject(level, i, j, 2);
			}
		}
	}
	else if (nChar == VK_RIGHT) {
		for (int i = 0; i < test.width; i++) {
			for (int j = 0; j < test.height; j++) {
				test.MoveObject(level, i, j, 3);
			}
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	// music_on_off
	if (point.x >= music_icon.GetLeft() && point.x <= music_icon.GetLeft() + music_icon.GetWidth() && point.y >= music_icon.GetTop() && point.y <= music_icon.GetTop() + music_icon.GetHeight()) {
		if (music_icon.GetFrameIndexOfBitmap() == 0) {
			music_icon.SetFrameIndexOfBitmap(1);
		}
		else {
			music_icon.SetFrameIndexOfBitmap(0);
		}	
	}

	//sound_on_off
	if (point.x >= sound_icon.GetLeft() && point.x <= sound_icon.GetLeft() + sound_icon.GetWidth() && point.y >= sound_icon.GetTop() && point.y <= sound_icon.GetTop() + sound_icon.GetHeight()) {
		if (sound_icon.GetFrameIndexOfBitmap() == 0) {
			sound_icon.SetFrameIndexOfBitmap(1);
		}
		else {
			sound_icon.SetFrameIndexOfBitmap(0);
		}
	}

	//exit
	if (choose_level.state == false) {
		if (point.x >= exit_icon.GetLeft() && point.x <= exit_icon.GetLeft() + exit_icon.GetWidth() && point.y >= exit_icon.GetTop() && point.y <= exit_icon.GetTop() + exit_icon.GetHeight()) {
			choose_level.state = true;
			transition.ToggleAnimation();
		}
	}

	//choose level
	if (choose_level.state == true) {
		if (choose_level.press_level_button(point) >= 0 && choose_level.press_level_button(point) <= 17) {
			level = choose_level.press_level_button(point);
			choose_level.state = false;
			transition.ToggleAnimation();
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (choose_level.state == true) {
		choose_level.Show();
		music_icon.ShowBitmap();
		sound_icon.ShowBitmap();
		show_transition();
	}

	else if (choose_level.state == false) {
		show_image_by_level();
		show_text_by_level();
		test.Show();
		show_transition();
	}
}

void CGameStateRun::show_image_by_level() {
	
	if (level <= 16) {
		background.SetFrameIndexOfBitmap(level - 1);
		background.ShowBitmap();
		music_icon.ShowBitmap();
		sound_icon.ShowBitmap();
		exit_icon.ShowBitmap();
	}
}

void CGameStateRun::show_text_by_level() {

	CDC *pDC = CDDraw::GetBackCDC();

	//CTextDraw::Print(pDC, 100, 100, std::to_string(test.width) + " " + std::to_string(test.height));
	
	if (level >= 1 && level <= 16) {
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_art.TextBorder(pDC, 15, 695, 4, "Level " + std::to_string(level));
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 15, 695, "Level " + std::to_string(level));
		CTextDraw::Print(pDC, 100, 100, std::to_string(test.width) + " " + std::to_string(test.height));

		if (level == 1) {

			CPoint ori = test.ReturnOri(level);
			for (int i = 0; i < test.width; i++) {
				for (int j = 0; j < test.height; j++) {
					CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j, std::to_string(i) + ", " + std::to_string(j));
					CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j + 20, test.PrintObjectType(i, j));
				}
			}
		}
	}

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_transition() {
	if (level <= 16) {
		transition.ShowBitmap();
	}
}
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
	map.Matrix(level);
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
	"resources/transition6.bmp"
		}, RGB(0, 0, 255));
	transition.SetTopLeft(0, 0);
	transition.SetAnimation(70, true);
	transition.ToggleAnimation();

	clear_pic.LoadBitmapByString({
	"resources/clear1.bmp",
	"resources/clear2.bmp",
	"resources/clear3.bmp",
	"resources/clear4.bmp",
	"resources/clear5.bmp",
	"resources/clear6.bmp",
	"resources/clear7.bmp"
		}, RGB(0, 0, 255));
	clear_pic.SetTopLeft(0, 0);
	clear_pic.SetAnimation(55, true);
	clear_pic.ToggleAnimation();

	dead_pic.LoadBitmapByString({
	"resources/dead1.bmp",
	"resources/dead2.bmp",
	"resources/dead3.bmp",
	"resources/dead4.bmp",
	"resources/dead5.bmp",
	"resources/dead6.bmp",
	"resources/dead7.bmp"
		}, RGB(0, 0, 255));
	dead_pic.SetTopLeft(0, 0);
	dead_pic.SetAnimation(55, true);
	dead_pic.ToggleAnimation();

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
	clear_level.GoalLocation(1);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// enter

	if (nChar == VK_RETURN) {

		if (clear_level.IfClear(level, map)) {
			level++;
			if (level <= 16) {
				transition.ToggleAnimation();
				clear_level.GoalLocation(level);
				map.MapStepClear();
				map.Matrix(level);
			}
		}
	}
	else if (nChar == VK_UP || nChar == 0x57) {
		if (clear_level.IfClear(level, map) == false && dead.IfDead(level, map) == false) {
			map.MoveObject(level, 0);
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (dead.IfDead(level, map)) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_DOWN || nChar == 0x53) {
		if (clear_level.IfClear(level, map) == false && dead.IfDead(level, map) == false) {
			map.MoveObject(level, 1);
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (dead.IfDead(level, map)) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_LEFT || nChar == 0x41) {
		if (clear_level.IfClear(level, map) == false && dead.IfDead(level, map) == false) {
			map.MoveObject(level, 2);
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (dead.IfDead(level, map)) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_RIGHT || nChar == 0x44) {
		if (clear_level.IfClear(level, map) == false && dead.IfDead(level, map) == false) {
			map.MoveObject(level, 3);
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (dead.IfDead(level, map)) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == 0x52) {
		if (clear_level.IfClear(level, map) == false) {
			map.MapStepClear();
			map.Matrix(level);
		}
	}
	else if (nChar == 0x55) {
		if (clear_level.IfClear(level, map) == false) {
			map.Undo();
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
			map.MapStepClear();
			map.Matrix(level);
			clear_level.GoalLocation(level);
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
		CDC *pDC = CDDraw::GetBackCDC();
		choose_level.LevelText(pDC);
		CDDraw::ReleaseBackCDC();
		show_transition();
	}

	else if (choose_level.state == false) {

		show_image_by_level();
		show_text_by_level();
		map.Show();
		show_transition();

		if (clear_level.IfClear(level, map)) {
			clear_pic.ShowBitmap();
		}
		else if (dead.IfDead(level, map)) {
			dead_pic.ShowBitmap();
		}
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

		/*CTextDraw::Print(pDC, 100, 100, std::to_string(map.width) + " " + std::to_string(map.height));

		CPoint ori = moveori.ReturnOri(level);
		for (int i = 0; i < map.width; i++) {
			for (int j = 0; j < map.height; j++) {
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j, std::to_string(i) + ", " + std::to_string(j));
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j + 20, map.PrintObjectType(i, j));
			}
		}

		for (int i = 0; i < clear_level.width; i++) {
			for (int j = 0; j < clear_level.height; j++) {
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j + 40, std::to_string(clear_level.GetValue(i, j)));
			}
		}
		*/

		//CTextDraw::Print(pDC, 15, 100, "Clear? = " + std::to_string(clear_level.IfClear(level, map)));
		//CTextDraw::Print(pDC, 15, 130, "Dead? = " + std::to_string(dead.IfDead(level, map))); 

		//CTextDraw::Print(pDC, 200, 100, imagedatashow[Character]);
		
	}

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_transition() {
	if (level <= 16) {
		transition.ShowBitmap();
	}
}
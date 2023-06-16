#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Loading ...");	// 一開始的loading進度為0%
	Sleep(100);
	
	background.LoadBitmapByString({ "resources/initialize_background.bmp" });
	background.SetTopLeft(0, 0);

	title.LoadBitmapByString({ "resources/title1.bmp", "resources/title2.bmp" }, RGB(0, 0, 255));
	title.SetTopLeft(631, 349);
	title.SetAnimation(200, false);

	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CAudio::Instance() -> Play(AUDIO_TRANS);
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	title.ShowBitmap();
	draw_text();
}

void CGameStateInit::draw_text() {

	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
	text_art.TextBorder(pDC, 545,632, 3, "Press any key to start");

	CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 545, 632, "Press any key to start");

	CTextDraw::Print(pDC, 15, 695, "By NTUT-Kiri, NTUT-Shuan");

	CDDraw::ReleaseBackCDC();
}
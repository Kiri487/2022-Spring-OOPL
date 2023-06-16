#include "stdafx.h"
#include "../Library/gameutil.h"
#include "text_art.h"

TextArt::TextArt() {

}

void TextArt::TextBorder(CDC *pDC, int x, int y, int size, string s) {

	for (int i = (x - size), j = (y - size); i < (x + size) && j < (y + size); i++, j++) {
		CTextDraw::Print(pDC, i, y, s);
		CTextDraw::Print(pDC, i, y + size, s);
		CTextDraw::Print(pDC, i, y - size, s);
		CTextDraw::Print(pDC, x, j, s);
		CTextDraw::Print(pDC, x + size, j, s);
		CTextDraw::Print(pDC, x - size, j, s);
	}	
}
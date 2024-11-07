#pragma once
#include "DataStructure.h"
#include "Bin.h"
#include "HUD.h"
#include "Character.h"

class AirboneStack :public Stack {
private:
	int x0;
	int y0;
	int H;
	int groundPosY;
public:
	AirboneStack();
	void GetInfomationForCal(SDL_Rect charRect);
	void Push(Trash* trash, bool throwLeft);
	void ProjectileCalXY(const float& time, OrgBin& orgBin, RIOBin& rioBin, NRIOBin& nrioBin, EBin& eBin, VerticalHUD& verticalHUD);
	friend void CalPoint(Node* node, Bin* BinRect, VerticalHUD &verticalHUD, TrashType trashType);
	void airboneStackShow(SDL_Renderer* screen);
	bool isEmpty();
};
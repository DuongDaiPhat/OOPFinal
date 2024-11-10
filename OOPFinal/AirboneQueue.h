#pragma once
#include "DataStructure.h"
#include "Bin.h"
#include "HUD.h"
#include "Character.h"

class AirboneQueue :public Queue {
private:
	int x0;
	int y0;
	int H;
	int groundPosY;
public:
	AirboneQueue();
	void GetInfomationForCal(SDL_Rect charRect);
	void EnQueue(Trash* trash, bool throwLeft);
	void ProjectileCalXY(OrgBin& orgBin, RIOBin& rioBin, NRIOBin& nrioBin, EBin& eBin, VerticalHUD& verticalHUD);
	friend void CalPoint(Node* node, Bin* BinRect, VerticalHUD& verticalHUD, TrashType trashType);
	void AirboneQueueShow(SDL_Renderer* screen);
	bool isEmpty();
};
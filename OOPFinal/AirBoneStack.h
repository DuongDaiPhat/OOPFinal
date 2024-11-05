#pragma once
#include "DataStructure.h"
#include "TrashCan.h"
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
	void ProjectileCalXY(const float& time, OrgTrashCan& orgTrashCan, RIOTrashCan& rioTrashCan, NRIOTrashCan& nrioTrashCan, ETrashCan& eTrashCan, VerticalHUD& verticalHUD);
	friend void CalPoint(Node* node, TrashCan* TrashCanRect, VerticalHUD &verticalHUD, TrashType trashType);
	void airboneStackShow(SDL_Renderer* screen);
	bool isEmpty();
};
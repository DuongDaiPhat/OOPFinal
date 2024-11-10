#include "AirBonequeue.h"
#include <cmath>

const double PI = 3.14159265358979;
const int g = 10;
const float alpha = PI / 9;
const int v0 = 35;
AirboneQueue::AirboneQueue() {
	x0 = y0 = H = groundPosY = 0;
}
void AirboneQueue::GetInfomationForCal(SDL_Rect charRect) {
	this->x0 = charRect.x + 30;
	this->y0 = charRect.y + 50;
	this->H = charRect.h;
	this->groundPosY = charRect.y + charRect.h - 60;
}
void AirboneQueue::EnQueue(Trash* trash, bool throwLeft) {
	this->Queue::EnQueue(trash);
	this->SetThrowLeft(throwLeft);
	this->SetThrowingPosX(this->x0);
	this->SetThrowingPosY(this->y0);
	this->SetTime(0);
	this->SetTimeCal(0);
	this->SetStopPosition(groundPosY);
	this->SetAppeared();
	float timeToMaxHeight = 2;
}
void CalPoint(Node* node, Bin* bin, VerticalHUD& verticalHUD, TrashType binType) {
	SDL_Rect trashRect = node->trash->GetRect();
	SDL_Rect binRect = bin->GetRect();
	binRect = { binRect.x, binRect.y, binRect.w, binRect.h - 150};
	if (SDL_HasIntersection(&trashRect, &binRect)) {
		int trashPoint = node->trash->GetTrashPoint();
		node->isDisappeared = true;
		TrashType trashType = node->trash->GetTrashType();
		if (binType == trashType) {
			cout << "Giong" << endl;
			int point = verticalHUD.GetPoint() + node->trash->GetTrashPoint();
			verticalHUD.SetPoint(point);
			node->trash->SetRect(0, 0, 0, 0);
		}
		else {
			cout << "Khac" << endl;
			int point = verticalHUD.GetPoint() - node->trash->GetTrashPoint();
			verticalHUD.SetPoint(point);
			node->trash->SetRect(0, 0, 0, 0);
		}
	}
}
static void makeCoordinateValid(int &posX, int posY, SDL_Rect trashRect) {
	if (posY <= 435) {
		if (posX <= 770) {
			posX = trashRect.x;
		}
	}
	if (posX <= 0) {
		posX = 0;
	}
	else if (posX + trashRect.w >= 1690) {
		posX = 1690 - trashRect.w;
	}
}
//them & de gan la ban goc chu khong tao copy//
void AirboneQueue::ProjectileCalXY(OrgBin& orgBin, RIOBin& rioBin, NRIOBin& nrioBin, EBin& eBin, VerticalHUD& verticalHUD) {
	Node* temp = this->ReturnHead();
	while (temp != nullptr) {
		int _x0 = temp->throwPositionX;
		int _y0 = temp->throwPositionY;
		int stopPos = temp->stopPosition;
		temp->time += 0.5;
		temp->timeCal = temp->time/3;
		float trashWeight = static_cast<float>(temp->trash->GetTrashWeight());
		//x = x0 + vo*cos(a)*t;
		//y = y0 + v0*sin(a)*t + (1/2)g*t^2
		float _xPos, _yPos;
		if (!temp->throwLeft) {
			if (trashWeight == 0) {
				_xPos = _x0 + v0 * cos(alpha) * temp->timeCal;
			}
			else {
				_xPos = _x0 + (0.8 / trashWeight) * v0 * cos(alpha) * temp->timeCal;
			}
		}
		else {
			if (trashWeight == 0) {
				_xPos = _x0 - v0 * cos(alpha) * temp->timeCal;
			}
			else {
				_xPos = _x0 - (1 / trashWeight) * v0 * cos(alpha) * temp->timeCal;
			}
		}
		if (temp->timeCal <= temp->timeToMaxHeight) {
			_yPos = _y0 - v0 * temp->time * sin(alpha) - (1 / 2) - g * pow(temp->timeCal, 2);
		}
		else {
			_yPos = _y0 - v0 * temp->time * sin(alpha) - (1 / 2) + g * pow(temp->timeCal, 2);
		}
		int setPosX = round(_xPos);
		int setPosY = round(_yPos);
		SDL_Rect trashRect = temp->trash->GetRect();
		makeCoordinateValid(setPosX, setPosY, trashRect);
		if (_yPos < stopPos) {
			temp->trash->SetRect(setPosX, setPosY, trashRect.w, trashRect.h);
		}
		else {
			temp->trash->SetRect(setPosX, setPosY, trashRect.w, trashRect.h);
			temp->isDisappeared = true;
		}
		CalPoint(temp, &orgBin, verticalHUD, orgBin.GetType());
		CalPoint(temp, &rioBin, verticalHUD, rioBin.GetType());
		CalPoint(temp, &nrioBin, verticalHUD, nrioBin.GetType());
		CalPoint(temp, &eBin, verticalHUD, eBin.GetType());
		temp = temp->next;
	}
}
void AirboneQueue::AirboneQueueShow(SDL_Renderer* screen) {
	Node* temp = this->ReturnHead();
	while (temp != nullptr) {
		temp->trash->Render(screen, nullptr);
		temp = temp->next;
	}
}
bool AirboneQueue::isEmpty() {
	if (this->ReturnHead() == nullptr) {
		return true;
	}
	return false;
}
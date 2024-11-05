#include "AirBoneStack.h"
#include <cmath>

const double PI = 3.14159265358979;
const int g = 100;
AirboneStack::AirboneStack() {
	x0 = y0 = H = groundPosY = 0;
}
void AirboneStack::GetInfomationForCal(SDL_Rect charRect) {
	this->x0 = charRect.x + 30;
	this->y0 = charRect.y + 50;
	this->H = charRect.h;
	this->groundPosY = charRect.y + charRect.h - 55;
}
void AirboneStack::Push(Trash *trash, bool throwLeft) {
	this->Stack::Push(trash);
	this->SetThrowLeft(throwLeft);
	this->SetThrowingPosX(this->x0);
	this->SetThrowingPosY(this->y0);
	this->SetTime(0);
	this->SetStopPosition(groundPosY);
	this->SetAppeared();
	float timeToMaxHeight = 1.5;
}
void CalPoint(Node* node, TrashCan* trashCan, VerticalHUD &verticalHUD, TrashType trashCanType) {
	SDL_Rect trashRect = node->trash->GetRect();
	SDL_Rect trashCanRect = trashCan->GetRect();
	if (SDL_HasIntersection(&trashRect, &trashCanRect)) {
		int trashPoint = node->trash->GetTrashPoint();
		node->isDisappeared = true;
		cout << static_cast<int>(node->trash->GetTrashType()) << "-";
		cout << static_cast<int>(trashCanType) << endl;
		TrashType trashType = node->trash->GetTrashType();
		if (trashCanType == trashType) {
			cout << "Giong" << endl;
			int point = verticalHUD.GetPoint() + node->trash->GetTrashPoint();
			verticalHUD.SetPoint(point);
			node->trash->SetRect(0, 0, 0, 0);
		}
		else {
			cout <<"Khac" << endl;
			int point = verticalHUD.GetPoint() - node->trash->GetTrashPoint();
			verticalHUD.SetPoint(point);
			node->trash->SetRect(0, 0, 0, 0);
		}
	}
}
//them & de gan la ban goc chu khong tao copy//
void AirboneStack::ProjectileCalXY(const float &time,OrgTrashCan &orgTrashCan,RIOTrashCan &rioTrashCan, NRIOTrashCan &nrioTrashCan, ETrashCan &eTrashCan, VerticalHUD& verticalHUD) {
	cout << static_cast<int>(orgTrashCan.GetType()) << endl;
	Node* temp = this->ReturnHead();
	while (temp != nullptr) {
		int _x0 = temp->throwPositionX;
		int _y0 = temp->throwPositionY;
		int stopPos = temp->stopPosition;
		temp->time += time;
		cout << temp->time;
		int trashWeight = temp->trash->GetTrashWeight();
		//x = x0 + vo*cos(a)*t;
		//y = y0 + v0*sin(a)*t + (1/2)g*t^2
		float _xPos, _yPos;
		if (!temp->throwLeft) {
			_xPos = _x0 + 100 * cos(PI / 20) * temp->time;
		}
		else {
			_xPos = _x0 - 100 * cos(PI / 20) * temp->time;
		}
		if (temp->time <= temp->timeToMaxHeight) {
			_yPos = _y0 - 100 * temp->time * sin(PI / 12) - (1 / 2) - g * pow(temp->time, 2);
		}
		else {
			_yPos = _y0 - 100 * temp->time * sin(PI / 12) - (1 / 2) + g * pow(temp->time, 2);
		}
		int setPosX = round(_xPos);
		int setPosY = round(_yPos);
		SDL_Rect trashRect = temp->trash->GetRect();
		if (_yPos < stopPos) {
			temp->trash->SetRect(setPosX, setPosY, trashRect.w, trashRect.h);
		}
		else {
			temp->trash->SetRect(setPosX, setPosY, trashRect.w, trashRect.h);
			temp->isDisappeared = true;
		}
		CalPoint(temp, &orgTrashCan, verticalHUD, orgTrashCan.GetType());
		CalPoint(temp, &rioTrashCan, verticalHUD, rioTrashCan.GetType());
		CalPoint(temp, &nrioTrashCan, verticalHUD, nrioTrashCan.GetType());
		CalPoint(temp, &eTrashCan, verticalHUD, eTrashCan.GetType());
		temp = temp->next;
	}
}
void AirboneStack::airboneStackShow(SDL_Renderer* screen) {
	Node* temp = this->ReturnHead();
	while (temp != nullptr) {
		temp->trash->Render(screen, nullptr);
		temp = temp->next;
	}
}
bool AirboneStack::isEmpty() {
	if (this->ReturnHead() == nullptr) {
		return true;
	}
	return false;
}
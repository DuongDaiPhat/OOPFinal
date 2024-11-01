#include "TrashCan.h"
#include "BaseFunction.h"

bool OrgTrashCan::LoadTrashCan(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\trashCan\\OrganicTrashCan.png")) {
		cout << "Khong the tai thung rac huu co" << endl;
		return false;
	}
	this->SetRect(ORG_TRASH_CAN_POS_X, ORG_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
bool RIOTrashCan::LoadTrashCan(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\trashCan\\RecyclableInorganicTrashCan.png")) {
		cout << "Khong the tai thung rac vo co tai che" << endl;
		return false;
	}
	this->SetRect(RIO_TRASH_CAN_POS_X, RIO_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
bool NRIOTrashCan::LoadTrashCan(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\trashCan\\Non-RecyclableInorganicTrashCan.png")) {
		cout << "Khong the tai thung rac vo co khong tai che" << endl;
		return false;
	}
	this->SetRect(NRIO_TRASH_CAN_POS_X, NRIO_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
bool ETrashCan::LoadTrashCan(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\trashCan\\E-wasteTrashCan.png")) {
		cout << "Khong the tai thung rac rac thai dien tu" << endl;
		return false;
	}
	this->SetRect(E_TRASH_CAN_POS_X, E_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}

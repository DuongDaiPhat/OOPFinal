#include "Bin.h"
#include "BaseFunction.h"

TrashType Bin::GetType() const {
	return type;
}
bool OrgBin::LoadBin(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\bin\\OrganicBin.png")) {
		cout << "Khong the tai thung rac huu co" << endl;
		return false;
	}
	this->SetRect(ORG_TRASH_CAN_POS_X, ORG_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
OrgBin::OrgBin() {
	this->type =TrashType::Organic;
}
bool RIOBin::LoadBin(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\bin\\RecyclableOrganicBin.png")) {
		cout << "Khong the tai thung rac vo co tai che" << endl;
		return false;
	}
	this->SetRect(RIO_TRASH_CAN_POS_X, RIO_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
RIOBin::RIOBin() {
	this->type = TrashType::Reclyable;
}
bool NRIOBin::LoadBin(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\bin\\Non-RecyclableInorganicBin.png")) {
		cout << "Khong the tai thung rac vo co khong tai che" << endl;
		return false;
	}
	this->SetRect(NRIO_TRASH_CAN_POS_X, NRIO_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
NRIOBin::NRIOBin() {
	this->type = TrashType::NonReclyable;
}
bool EBin::LoadBin(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\bin\\E-wasteBin.png")) {
		cout << "Khong the tai thung rac rac thai dien tu" << endl;
		return false;
	}
	this->SetRect(E_TRASH_CAN_POS_X, E_TRASH_CAN_POS_Y, TRASH_CAN_WIDTH, TRASH_CAN_HEIGHT);
	return true;
}
EBin::EBin() {
	this->type = TrashType::Electronic;
}

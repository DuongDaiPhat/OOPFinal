#include "HUD.h"
#include "BaseFunction.h"
#include <string>

VerticalHUD::VerticalHUD() {
	point = speed = 0;
	speedTextTexture = nullptr;
	pointTextTexture = nullptr;
}
VerticalHUD::~VerticalHUD() {
	point = speed = 0;
	SDL_DestroyTexture(speedTextTexture);
	speedTextTexture = nullptr;
	SDL_DestroyTexture(pointTextTexture);
	pointTextTexture = nullptr;
}
void VerticalHUD::SetPoint(const int& CharPoint){
	point = CharPoint;
}
void VerticalHUD::SetSpeed(const int& CharSpeed) {
	speed = CharSpeed;
}
int VerticalHUD::GetPoint() const {
	return point;
}
int VerticalHUD::GetSpeed() const {
	return speed;
}
bool VerticalHUD::LoadHUD(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\HUD\\stats.png")) {
		cout << "HUD loi" << endl;
		return false;
	}
	this->SetRect(VERTICAL_HUD_POS_X, VERTICAL_HUD_POS_Y, VERTICAL_HUD_WEIGHT, VERTICAL_HUD_HEIGHT);
	return true;
}
bool VerticalHUD::RenderStat(SDL_Renderer* screen, TTF_Font *font) {
	string speedText = to_string(speed);
	string pointText = to_string(point);
	SDL_Color textColor = { TEXT_COLOR_R, TEXT_COLOR_G,TEXT_COLOR_B,TEXT_TRANSPARENCY };
	SDL_Surface* speedTextSurface = TTF_RenderText_Solid(font, speedText.c_str(), textColor);
	SDL_Surface* pointTextSurface = TTF_RenderText_Solid(font, pointText.c_str(), textColor);
	if (!speedTextSurface || !pointTextSurface) {
		cout << "Khong the tao surface" << endl;
		return false;
	}
	speedTextTexture = SDL_CreateTextureFromSurface(screen, speedTextSurface);
	if (speedTextTexture == nullptr) {
		cout << "Khong the tai texture cua speed text" << endl;
		return false;
	}
	pointTextTexture = SDL_CreateTextureFromSurface(screen, pointTextSurface);
	if (pointTextTexture == nullptr) {
		cout << "Khong the tai texture cua point text" << endl;
		return false;
	}
	SDL_Rect speedRenderQuad = { SPEED_TEXT_POS_X, SPEED_TEXT_POS_Y, speedTextSurface->w, speedTextSurface->h };
	SDL_Rect pointRenderQuad = { POINT_TEXT_POS_X, POINT_TEXT_POS_Y, pointTextSurface->w, pointTextSurface->h };
	SDL_FreeSurface(speedTextSurface);
	SDL_FreeSurface(pointTextSurface);
	this->Render(screen, nullptr);
	SDL_RenderCopy(screen, pointTextTexture, nullptr, &pointRenderQuad);
	SDL_RenderCopy(screen, speedTextTexture, nullptr, &speedRenderQuad);
	return true;
}

bool InventoryBar::LoadInventoryBar(SDL_Renderer* screen) {
	if (!this->LoadImage(screen, "..\\assets\\HUD\\inventory.png")) {
		cout << "Khong the load thanh luu tru " << endl;
		return false;
	}
	this->SetRect(INVENTORYBAR_POSX, INVENTORYBAR_POSY, INVENTORYBAR_WIDTH, INVENTORYBAR_HEIGHT);
	if (!this->baloIcon.LoadImage(screen, "..\\assets\\HUD\\Balo.png")) {
		cout << "Khong the load Balo icon" << endl;
		return false;
	}
	this->baloIcon.SetRect(BALOICON_POSX, BALOICON_POSY, BALOICON_WIDTH, BALOICON_HEIGHT);
	return true;
}
void InventoryBar::InventoryBarRender(SDL_Renderer* screen) {
	this->Render(screen, nullptr);
	this->baloIcon.Render(screen, nullptr);
}
Inventory::Inventory() {
	this->InventorySetUp();
}
bool Inventory::IsFull() const{
	return isFull;
}
void Inventory::InventorySetUp() {
	isFull = false;
	inventoryMinY = INVENTORYBAR_POSY + INVENTORYBAR_HEIGHT - 20;
	inventoryMaxY = INVENTORYBAR_POSY + BALOICON_HEIGHT + 25;
	inventoryPresentY = inventoryMinY;
	inventoryPosX = INVENTORYBAR_POSX;
}
void Inventory::AddTrashToInventory(Character& character,Trash* trash) {
	if (isFull) {
		cout << "Balo day" << endl;
		return;
	}
	SDL_Rect trashRect = trash->GetRect();
	int newTrashWidth = trashRect.w;
	int newTrashHeight = trashRect.h;
	if (inventoryMaxY >= inventoryPresentY - newTrashHeight) {
		isFull = true;
		cout << "Balo day" << endl;
	}
	else {
		if (trashRect.w < 50) {
			inventoryPosX = INVENTORYBAR_POSX + 35;
		}
		else if (trashRect.w <= 60 && trashRect.w >= 50) {
			inventoryPosX = INVENTORYBAR_POSX + 23;
		}
		else {
			inventoryPosX = INVENTORYBAR_POSX + 10;
		}
		int trashWeight = trash->GetTrashWeight();
		character.charSpeed -= trashWeight;

		trash->SetRect(inventoryPosX, inventoryPresentY - newTrashHeight, newTrashWidth, newTrashHeight);
		trashInInventory.Push(trash);
		inventoryPresentY -= newTrashHeight + 5;
	}
}
Trash* Inventory::RemoveTrashFromInventory(Character &character) {
	Trash* trash = trashInInventory.Pop();
	if (trash != nullptr) {
		int trashWeight = trash->GetTrashWeight();
		character.charSpeed += trashWeight;
	}
	isFull = false;
	return trash;
}
void Inventory::InventoryShow(SDL_Renderer* screen) const{
	Node* temp = trashInInventory.stack.pHead;
	while (temp != nullptr) {
		temp->trash->Render(screen, nullptr);
		temp = temp->next;
	}
}
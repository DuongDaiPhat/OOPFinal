#pragma once
#include "BaseObject.h"
#include "Character.h"
#include "DataStructure.h"
class VerticalHUD:public BaseObject {
private:
	SDL_Texture* speedTextTexture;
	SDL_Texture* pointTextTexture;
	int point;
	int speed;
public:
	VerticalHUD();
	~VerticalHUD();
	void SetPoint(const int  &CharPoint);
	void SetSpeed(const int  &CharSpeed);
	int GetPoint() const;
	int GetSpeed() const;
	bool LoadHUD(SDL_Renderer* screen);
	bool RenderStat(SDL_Renderer* screen, TTF_Font* font);
	friend class Inventory;
};
class InventoryBar :public BaseObject {
private:
	BaseObject baloIcon;
public:
	bool LoadInventoryBar(SDL_Renderer* screen);
	void InventoryBarRender(SDL_Renderer* screen);
};

class Inventory{
private:
	bool isFull;
	bool isEmpty;
	int inventoryMinY;
	int inventoryMaxY;
	int inventoryPresentY;
	int inventoryPosX;
	Stack trashInInventory;
public:
	Inventory();
	void InventorySetUp();
	void AddTrashToInventory(Character &character, Trash* trash);
	Trash* GetTrashFromInventory(Character &character);
	void InventoryShow(SDL_Renderer* screen) const;
	bool IsFull() const;
	bool IsEmpty()const;
	//test
	int GetInventoryPresentY() const;
	friend class InventoryBar;
	friend class Character;	
};

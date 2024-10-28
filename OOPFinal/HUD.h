#pragma once
#include "BaseObject.h"
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
};
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
	speedTextTexture = nullptr;
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
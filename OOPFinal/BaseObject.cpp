#include "BaseObject.h"

BaseObject::BaseObject() {
	objectTexture = nullptr;
	objectRect.x = 0;
	objectRect.y = 0;
	objectRect.w = 0;
	objectRect.h = 0;
}
BaseObject::~BaseObject() {
	Free();
}
void BaseObject::SetRect(int x, int y, int w, int h) {
	objectRect = { x,y,w,h };
}
SDL_Rect BaseObject::GetRect() {
	return objectRect;
}
SDL_Texture* BaseObject::GetTexture() {
	return objectTexture;
}
bool BaseObject::LoadImage(const string file_path) {
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* newSurface = IMG_Load(file_path.c_str());
	if (newSurface == nullptr) {
		cout << "Khong the load surface" << endl;
		return false;
	}
	newTexture = SDL_CreateTextureFromSurface(g_screen, newSurface);
	if (newTexture == nullptr) {
		cout << "Khong the tai texture" << endl;
		return false;
	}
	SDL_FreeSurface(newSurface);
	objectTexture = newTexture;
	return true;
}
void BaseObject::Render(SDL_Renderer* screen, SDL_Rect* clip) {
	SDL_Rect tempRect = objectRect;
	SDL_RenderCopy(screen, objectTexture, clip, &tempRect);
}
void BaseObject::Free() {
	SDL_DestroyTexture(objectTexture);
	objectRect = { 0,0,0,0 };
}
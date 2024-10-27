#pragma once
#include "BaseFunction.h"

class BaseObject {
protected:
	SDL_Texture* objectTexture;
	SDL_Rect objectRect;
public:
	BaseObject();
	virtual ~BaseObject();
	SDL_Rect GetRect();
	void SetRect(int x, int y, int w, int h);
	SDL_Texture* GetTexture();
	bool LoadImage(SDL_Renderer *g_screen, const string file_path);
	void Render(SDL_Renderer* screen, SDL_Rect* clip);
	void Free();
};
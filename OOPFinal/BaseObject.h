#pragma once
#include "BaseFunction.h"

class BaseObject {
protected:
	SDL_Texture* objectTexture;
	SDL_Rect objectRect;
public:
	BaseObject();
	~BaseObject();
	SDL_Rect GetRect();
	void SetRect(int x, int y, int w, int h);
	SDL_Texture* GetTexture();
	bool LoadImage(const string file_path);
	void Render(SDL_Renderer* screem, SDL_Rect* clip);
	void Free();
};
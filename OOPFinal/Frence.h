#pragma once
#include "BaseObject.h"
class Frence :public BaseObject {
protected:
	bool isVertical;
	SDL_Rect topBoundary;
	SDL_Rect botBoundary;
public:
	void SetVertical();
	void SetHorizontal();
	bool VerticalCheck();
	bool IsCollisionCheck(int x, int y, int w, int h);
	void SetBoundary();
};
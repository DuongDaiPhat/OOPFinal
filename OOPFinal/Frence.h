#pragma once
#include "BaseObject.h"
class Frence :public BaseObject {
protected:
	bool isVertical;
	SDL_Rect topBoundary;
	SDL_Rect botBoundary;
public:
	Frence();
	void SetVertical();
	void SetHorizontal();
	bool VerticalCheck() const;
	bool IsCollisionCheck(int x, int y, int w, int h);
	void SetBoundary();
};
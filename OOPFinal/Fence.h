#pragma once
#include "BaseObject.h"
class Fence :public BaseObject {
protected:
	bool isVertical;
	SDL_Rect topBoundary;
	SDL_Rect botBoundary;
public:
	Fence();
	void SetVertical();
	void SetHorizontal();
	bool VerticalCheck() const;
	bool IsCollisionCheck(int x, int y, int w, int h);
	void SetBoundary();
};
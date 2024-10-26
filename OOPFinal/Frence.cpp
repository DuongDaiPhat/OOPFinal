#include "Frence.h"

void Frence::SetHorizontal() {
	isVertical = false;
}
void Frence::SetVertical() {
	isVertical = true;
}
bool Frence::VerticalCheck() {
	return isVertical;
}
bool Frence::IsCollisionCheck(int x, int y, int w, int h) {
	SDL_Rect characterRect = { x,y,w,h };
	if (!isVertical) {
		if (SDL_HasIntersection(&objectRect, &characterRect)) {

			return true;
		}
		return false;
	}
	else {
		if (SDL_HasIntersection(&topBoundary, &characterRect) && SDL_HasIntersection(&botBoundary, &characterRect)) {
			cout << "Dung " << endl;
			return true;
		}
		return false;
	}
}
void Frence::SetBoundary() {
	topBoundary.x = objectRect.x;
	topBoundary.y = objectRect.y - 30;
	topBoundary.w = objectRect.w;
	topBoundary.h = 1;
	
	botBoundary.x = objectRect.x;
	botBoundary.y = topBoundary.y + 121;
	botBoundary.w = objectRect.w;
	botBoundary.h = 1;
}
#include "Fence.h"

Fence::Fence() {
	isVertical = false;
	topBoundary = { 0,0,0,0 };
	botBoundary = { 0,0,0,0 };
}
void Fence::SetHorizontal() {
	isVertical = false;
}
void Fence::SetVertical() {
	isVertical = true;
}
bool Fence::VerticalCheck() const {
	return isVertical;
}
bool Fence::IsCollisionCheck(int x, int y, int w, int h) {
	SDL_Rect characterRect = { x,y,w,h };
	if (!isVertical) {
		if (SDL_HasIntersection(&objectRect, &characterRect)) {
			return true;
		}
		return false;
	}
	else {
		if (SDL_HasIntersection(&topBoundary, &characterRect) && SDL_HasIntersection(&botBoundary, &characterRect)) {
			return true;
		}
		return false;
	}
}
void Fence::SetBoundary() {
	topBoundary.x = objectRect.x;
	topBoundary.y = objectRect.y - 30;
	topBoundary.w = objectRect.w;
	topBoundary.h = 1;
	
	botBoundary.x = objectRect.x;
	botBoundary.y = topBoundary.y + 121;
	botBoundary.w = objectRect.w;
	botBoundary.h = 1;
}
#pragma once
#include "BaseObject.h"

class Tree : public BaseObject {
protected:
	bool type[3];
public:
	Tree();
	void setType(int type);
	bool loadTree(SDL_Renderer* screen);
};

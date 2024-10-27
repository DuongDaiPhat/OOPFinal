#pragma once
#include "BaseObject.h"

class TrashCan: public BaseObject{
public:
	virtual bool LoadTrashCan(SDL_Renderer* screen) = 0;
};

class OrgTrashCan:public TrashCan{
public:
	bool LoadTrashCan(SDL_Renderer* screen);
};
class RIOTrashCan :public TrashCan {
public:
	bool LoadTrashCan(SDL_Renderer* screen);
};
class NRIOTrashCan :public TrashCan {
public:
	bool LoadTrashCan(SDL_Renderer* screen);
};
class ETrashCan :public TrashCan {
public:
	bool LoadTrashCan(SDL_Renderer* screen);
};

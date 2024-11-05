#pragma once
#include "BaseObject.h"
#include "Trash.h"

class TrashCan: public BaseObject{
protected:
	TrashType type;
public:
	virtual bool LoadTrashCan(SDL_Renderer* screen) = 0;
	TrashType GetType() const;
};

class OrgTrashCan:public TrashCan{
public:
	OrgTrashCan();
	bool LoadTrashCan(SDL_Renderer* screen);
};
class RIOTrashCan :public TrashCan {
public:
	RIOTrashCan();
	bool LoadTrashCan(SDL_Renderer* screen);
};
class NRIOTrashCan :public TrashCan {
public:
	NRIOTrashCan();
	bool LoadTrashCan(SDL_Renderer* screen);
};
class ETrashCan :public TrashCan {
public:
	ETrashCan();
	bool LoadTrashCan(SDL_Renderer* screen);
};

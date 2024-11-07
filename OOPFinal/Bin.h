#pragma once
#include "BaseObject.h"
#include "Trash.h"

class Bin: public BaseObject{
protected:
	TrashType type;
public:
	virtual bool LoadBin(SDL_Renderer* screen) = 0;
	TrashType GetType() const;
};

class OrgBin:public Bin{
public:
	OrgBin();
	bool LoadBin(SDL_Renderer* screen);
};
class RIOBin :public Bin {
public:
	RIOBin();
	bool LoadBin(SDL_Renderer* screen);
};
class NRIOBin :public Bin {
public:
	NRIOBin();
	bool LoadBin(SDL_Renderer* screen);
};
class EBin :public Bin {
public:
	EBin();
	bool LoadBin(SDL_Renderer* screen);
};

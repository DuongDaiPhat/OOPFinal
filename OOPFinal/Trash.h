#pragma once
#include "BaseObject.h"

typedef struct TrashProperties {
	int points;
	int weight;
	int decompositionTime;
}TrashProperties;
enum class TrashType {
	None = 0,
	Organic = 1,
	Reclyable = 2,
	NonReclyable = 3,
	Electronic = 4
};
enum class TrashSpecificType {
	None,
	BananaPeel, AppleCore, BigStick, SmallStick, RedApple, PurpleApple,
	Can, GlassBottle, PapperBag, RubberDuck, RubberGloves,WaterBottle,
	HouseHoldTrash, InsectSpray, PlasticBag, Sponge,
	Battery, ElectricCircuit, ElectricWire, LightBulb
};
class Trash:public BaseObject {
private:
	TrashProperties properties;
	TrashType type;
	TrashSpecificType specificType;
public:
	Trash();
	Trash(TrashType type, TrashSpecificType stype);
	Trash(const Trash &copyTrash);
	void TrashSetProperties();
	int GetTrashPoint() const;
	int GetTrashWeight() const;
	int GetTrashDeTime() const;
	TrashType GetTrashType() const;
	TrashSpecificType GetTrashSpecificType() const;
	bool LoadTrash(SDL_Renderer* screen);
	bool operator==(Trash trash2);
	void Disappear();
};

//properties stat of Trash
//Weight;
const int TINY_TRASH_WEIGHT = 0;
const int SMALL_TRASH_WEIGHT = 1;
const int NORMAL_TRASH_WEIGHT = 1;
const int BIG_TRASH_WEIGHT = 2;
const int HUGE_TRASH_WEIGHT = 3;
//Points
const int TINY_TRASH_POINTS = 2;
const int SMALL_TRASH_POINTS = 5;
const int NORMAL_TRASH_POINTS = 11;
const int BIG_TRASH_POINTS = 17;
const int HUGE_TRASH_POINTS = 23;
//Decomposition Time (Minutes)
const int BANANAPEEL_DT = 3;
const int APPLECORE_DT = 5;
const int BIGSTICK_DT = 15;
const int SMALLSTICK_DT = 10;
const int REDAPPLE_DT = 5;
const int PURPLEAPPLE_DT = 5;
const int PAPPERBAG_DT = 4;

//Trash Size:
const int TINY_TRASH_WIDTH = 35;
const int TINY_TRASH_HEIGHT = 35;
const int SMALL_TRASH_WIDTH = 45;
const int SMALL_TRASH_HEIGHT = 45;
const int NORMAL_TRASH_WIDTH = 50;
const int NORMAL_TRASH_HEIGHT = 50;
const int BIG_TRASH_WIDTH = 60;
const int BIG_TRASH_HEIGHT = 60;
const int HUGE_TRASH_WIDTH = 100;
const int HUGE_TRASH_HEIGHT = 100;

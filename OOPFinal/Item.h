#pragma once
#include "BaseObject.h"

typedef struct itemType {
	bool redApple;//1
	bool purpleApple;//2
	bool bigStick;//3
	bool smallStick;//4
}iType;
class Item :public BaseObject {
protected:
	iType type;
	int value;
	int weight;
public:
	Item();
	void SetType(int typeNum);
	void SetValue(int value);
	int GetValue();
	void SetWeight(int weight);
	int GetWeight();
	bool LoadItem(SDL_Renderer* screen);

};
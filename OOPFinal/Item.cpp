#include "Item.h"
#include <random>

Item::Item() {
	type.bigStick = false;
	type.purpleApple = false;
	type.redApple = false;
	type.smallStick = false;
}
void Item::SetType(int typeNum) {
	switch (typeNum) {
		case 1: {
			type.redApple = true;
			type.purpleApple = false;
			type.bigStick = false;
			type.smallStick = false;
			break;
		}
		case 2: {
			type.redApple = false;
			type.purpleApple = true;
			type.bigStick = false;
			type.smallStick = false;
			break;
		}
		case 3: {
			type.redApple = false;
			type.purpleApple = false;
			type.bigStick = true;
			type.smallStick = false;
			break;
		}
		case 4: {
			type.redApple = false;
			type.purpleApple = false;
			type.bigStick = false;
			type.smallStick = true;
			break;
		}
	}
}
void Item::SetValue(int value) {
	this->value = value;
}
int Item::GetValue() {
	return value;
}
void Item::SetWeight(int weight) {
	this->weight = weight;
}
int Item::GetWeight() {
	return weight;
}
bool Item::LoadItem(SDL_Renderer *screen) {
	if (type.redApple) {
		if (!BaseObject::LoadImage(screen, "..\\assets\\item\\RedApple.png")) {
			cout << "Fail to load Red Apple" << endl;
			return false;
		}
	}
	else if (type.purpleApple) {
		if (!BaseObject::LoadImage(screen, "..\\assets\\item\\PurpleApple.png")) {
			cout << "Fail to load Purple Apple" << endl;
			return false;
		}
	}
	else if (type.bigStick) {
		if (!BaseObject::LoadImage(screen, "..\\assets\\item\\BigStick.png")) {
			cout << "Fail to load Big Stick" << endl;
			return false;
		}
	}
	else if (type.smallStick) {
		if (!BaseObject::LoadImage(screen, "..\\assets\\item\\SmallStick.png")) {
			cout << "Fail to load Small Stick" << endl;
			return false;
		}
	}
	std::random_device rd;  // Sử dụng thiết bị ngẫu nhiên để tạo seed
	std::mt19937 gen(rd()); // Sử dụng Mersenne Twister làm bộ sinh số ngẫu nhiên
	std::uniform_int_distribution<> disX(1360, 1664);  // Tạo phân phối số nguyên trong khoảng [1, 1664]

	int xPos = disX(gen);
	int yPos;
	if (xPos < 1272) {
		std::uniform_int_distribution<> disY(860, 1000);
		yPos = disY(gen);	
	}
	else {
		std::uniform_int_distribution<> disY(0, 900);
		yPos = disY(gen);
	}
	this->SetRect(xPos, yPos, 60, 60);
}
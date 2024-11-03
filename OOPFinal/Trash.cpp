#include "Trash.h"
#include "random"
using namespace std;

Trash::Trash() {
	properties.points = properties.weight = properties.decompositionTime = 0;
	type = TrashType::None;
	specificType = TrashSpecificType::None;
}
Trash::Trash(TrashType t, TrashSpecificType st) {
	type = t;
	specificType = st;
	properties.decompositionTime = -1;
	this->TrashSetProperties();
}
Trash::Trash(const Trash& copyTrash) {
	this->properties = copyTrash.properties;
	this->type = copyTrash.type;
	this->specificType = copyTrash.specificType;
}
int Trash::GetTrashPoint() const{
	return properties.points;
}
int Trash::GetTrashWeight() const{
	return properties.weight;
}
int Trash::GetTrashDeTime()const {
	return properties.decompositionTime;
}
TrashType Trash::GetTrashType() const {
	return this->type;
}
TrashSpecificType Trash::GetTrashSpecificType()const {
	return this->specificType;
}
bool Trash::operator==(Trash trash2) {
	SDL_Rect trash2Rect = trash2.GetRect();
	if (objectRect.x != trash2Rect.x || objectRect.y != trash2Rect.y || objectRect.w != trash2Rect.w || objectRect.h != trash2Rect.h) {
		return false;
	}
	if (type != trash2.GetTrashType()) {
		return false;
	}
	if (specificType != trash2.GetTrashSpecificType()) {
		return false;
	}
	return true;
}
static int RandomX() {
	random_device rd;  // Sử dụng thiết bị ngẫu nhiên để tạo seed
	mt19937 gen(rd()); // Sử dụng Mersenne Twister làm bộ sinh số ngẫu nhiên
	uniform_int_distribution<> disX(0, 1664);  // Tạo phân phối số nguyên trong khoảng [0, 1664]
	int xPos = disX(gen);
	return xPos;
}
static int RandomY(int xPos) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disY(0, 908);
	int yPos;
	do {
		yPos = disY(gen);
	} while (
		xPos <= 832 && yPos <= 640 || 
		((768 <= xPos && xPos <= 1152) || (128 <= xPos && xPos <= 512)) && (768 <= yPos && yPos <= 960) ||
		(1344 <= xPos && xPos <= 1572) && ((64 <= yPos && yPos <= 512) || (576 <= yPos && yPos <= 896))
		);
	return yPos;
}
bool Trash::LoadTrash(SDL_Renderer* screen){
	int xPos = RandomX();
	int yPos = RandomY(xPos);
	switch (specificType) {
	case TrashSpecificType::BananaPeel: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\BananaPeel.png")) {
			cout << "Khong the load qua chuoi" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, TINY_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::AppleCore: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\AppleCore.png")) {
			cout << "Khong the load cui tao" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, TINY_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::BigStick: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\BigStick.png")) {
			cout << "Khong the load gay lon" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, HUGE_TRASH_WIDTH, HUGE_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::SmallStick: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\SmallStick.png")) {
			cout << "Khong the load gay nho" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, TINY_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::RedApple: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\RedApple.png")) {
			cout << "Khong the load tao do" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, SMALL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::PurpleApple: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\OrganicWaste\\PurpleApple.png")) {
			cout << "Khong the load tao tim" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, SMALL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::Can: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\can.png")) {
			cout << "Khong the load cai lon" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, NORMAL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::GlassBottle: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\GlassBottle.png")) {
			cout << "Khong the load chai thuy tinh" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, BIG_TRASH_WIDTH, NORMAL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::PapperBag: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\PaperBag.png")) {
			cout << "Khong the load tui giay" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, BIG_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::RubberDuck: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\RubberDuck.png")) {
			cout << "Khong the load vit cao su" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, TINY_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::RubberGloves: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\RubberGloves.png")) {
			cout << "Khong the load gang tay cao su" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, NORMAL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::WaterBottle: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\RecyclableInorganicWaste\\WaterBottle.png")) {
			cout << "Khong the load chai nuoc" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, BIG_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::HouseHoldTrash: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\Non-RecyclableOrganicWaste\\householdTrash.png")) {
			cout << "Khong the load rac thai sinh hoat" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, HUGE_TRASH_WIDTH, HUGE_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::InsectSpray: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\Non-RecyclableOrganicWaste\\insectBugSpray.png")) {
			cout << "Khong the load binh xit con trung" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, BIG_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::PlasticBag: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\Non-RecyclableOrganicWaste\\plasticBag.png")) {
			cout << "Khong the load tui nhua" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, SMALL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::Sponge: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\Non-RecyclableOrganicWaste\\sponge.png")) {
			cout << "Khong the load mieng bot bien" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH, TINY_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::Battery: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\E-Waste\\Battery.png")) {
			cout << "Khong the load pin hong" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, TINY_TRASH_WIDTH - 20, TINY_TRASH_HEIGHT - 20);
		break;
	}
	case TrashSpecificType::ElectricCircuit: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\E-Waste\\ElectricCircuit.png")) {
			cout << "Khong the load bang mach hong" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, SMALL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::ElectricWire: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\E-Waste\\ElectricWire.png")) {
			cout << "Khong the load day dien hong" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, SMALL_TRASH_WIDTH, SMALL_TRASH_HEIGHT);
		break;
	}
	case TrashSpecificType::LightBulb: {
		if (!this->LoadImage(screen, "..\\assets\\waste\\E-Waste\\LightBulb.png")) {
			cout << "Khong the load bong den hong" << endl;
			return false;
		}
		this->SetRect(xPos, yPos, NORMAL_TRASH_WIDTH, NORMAL_TRASH_HEIGHT);
		break;
	}
	}
	return true;
}
void Trash::Disappear() {

}
void Trash::TrashSetProperties() {
	switch (specificType) {
	case TrashSpecificType::BananaPeel: {
		properties.points = TINY_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		properties.decompositionTime = BANANAPEEL_DT;
		break;
	}
	case TrashSpecificType::AppleCore:{
		properties.points = TINY_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		properties.decompositionTime = APPLECORE_DT;
		break;
	}
	case TrashSpecificType::BigStick:{
		properties.points = HUGE_TRASH_POINTS;
		properties.weight = HUGE_TRASH_WEIGHT;
		properties.decompositionTime = BIGSTICK_DT;
		break;
	}
	case TrashSpecificType::SmallStick:{
			properties.points = TINY_TRASH_POINTS;
			properties.weight = TINY_TRASH_WEIGHT;
			properties.decompositionTime = SMALLSTICK_DT;
			break;
		}
	case TrashSpecificType::RedApple:{
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = SMALL_TRASH_WEIGHT;
		properties.decompositionTime = REDAPPLE_DT;
		break;
	}
	case TrashSpecificType::PurpleApple:{
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = SMALL_TRASH_WEIGHT;
		properties.decompositionTime = PURPLEAPPLE_DT;
		break;
	}
	case TrashSpecificType::Can:{
			properties.points = SMALL_TRASH_POINTS;
			properties.weight = SMALL_TRASH_WEIGHT;
			break;
	}
	case TrashSpecificType::GlassBottle:{
			properties.points = NORMAL_TRASH_POINTS;
			properties.weight = NORMAL_TRASH_WEIGHT;
			break;
	}
	case TrashSpecificType::PapperBag :{
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::RubberDuck:{
		properties.points = TINY_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::RubberGloves: {
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::WaterBottle:{
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = SMALL_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::HouseHoldTrash: {
		properties.points = BIG_TRASH_POINTS;
		properties.weight = BIG_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::InsectSpray : {
		properties.points = NORMAL_TRASH_POINTS;
		properties.weight = NORMAL_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::PlasticBag: {
		properties.points = SMALL_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::Sponge:{
		properties.points = TINY_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::Battery: {
		properties.points = HUGE_TRASH_POINTS;
		properties.weight = TINY_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::ElectricCircuit: {
		properties.points = HUGE_TRASH_POINTS;
		properties.weight = SMALL_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::ElectricWire: {
		properties.points = BIG_TRASH_POINTS;
		properties.weight = SMALL_TRASH_WEIGHT;
		break;
	}
	case TrashSpecificType::LightBulb: {
		properties.points = NORMAL_TRASH_POINTS;
		properties.weight = NORMAL_TRASH_WEIGHT;
		break;
	}
	}
}

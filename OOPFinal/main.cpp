#include "BaseFunction.h"
#include "BaseObject.h"
#include "Character.h"
#include "House.h"
#include "Fence.h"
#include "Tree.h"
#include "TrashCan.h"
#include "HUD.h"
#include "Trash.h"
#include "MapGrid.h"
#include "AirBoneStack.h"

//init
static bool createWindow() {
	g_window = SDL_CreateWindow("Viu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr) {
		cout << "Khoi tao cua so that bai" << endl;
		return false;
	}
	return true;
}
static bool createRenderer() {
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_screen == nullptr) {
		cout << "Khoi tao man hinh that bai" << endl;
		return false;
	}
	return true;
}
static bool createFont() {
	g_font = TTF_OpenFont("..\\assets\\font\\Tiny5-Regular.ttf", TEXT_SIZE);
	if (g_font == nullptr) {
		cout << "Khoi tao font chu that bai" << endl;
		return false;
	}
	return true;
}
static bool initGame() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Khong the khoi tao tro choi" << endl;
		return false;
	}
	if (!createWindow()) {
		SDL_DestroyWindow(g_window);
		return false;
	}
	if (!createRenderer()) {
		SDL_DestroyRenderer(g_screen);
		SDL_DestroyWindow(g_window);
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG)) {
		SDL_DestroyRenderer(g_screen);
		SDL_DestroyWindow(g_window);
		return false;
	}
	if (TTF_Init() < 0 || !createFont()){
		cout << "Khong the khoi tao font chu" << endl;
		SDL_DestroyRenderer(g_screen);
		SDL_DestroyWindow(g_window);
		return false;
	}
	return true;
}
//End
static void close() {
	SDL_DestroyRenderer(g_screen);
	g_screen = nullptr;
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	TTF_CloseFont(g_font);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
//Background:
BaseObject background;
static bool loadBackground() {
	if (!background.LoadImage(g_screen,"..\\assets\\background\\FinalGameBG1.png")) {
		cout << "Khong the tai hinh nen" << endl;
		return false;
	}
	background.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	return true;
}
//VerticalHUD
VerticalHUD verticalHUD;
//InventoryBar
InventoryBar inventoryBar;
//Inventory
Inventory inventory;
//Character:
Character redhood;
static bool loadRedHood() {
	if (!redhood.LoadCharacterImage(g_screen, "..\\assets\\characterSpriteSheet\\RedHoodIdleRight.png")) {
		cout << "Khong the tai nhna vat" << endl;
		return false;
	}
	redhood.SetSpawn(242, 436);
	return true;
}
//House
House house;
static bool loadHouse() {
	if (!house.LoadImage(g_screen, "..\\assets\\other\\House.png")) {
		cout << "Khong the tai anh nha" << endl;
		return false;
	}
	return true;
}
//Fence
Fence fence[4];
Fence vFence[3];
//Horizontal Fence
static bool loadFence(int FenceNum) {
	for (int i = 0; i < FenceNum; i++) {
		if (!fence[i].LoadImage(g_screen, "..\\assets\\other\\FenceHorizontal.png")) {
			cout << "Khong the tai anh hang rao thu" << i << endl;
			return false;
		}
	}
	return true;
}
static void FenceShow(int FenceNum) {
	for (int i = 0; i < FenceNum; i++) {
		fence[i].Render(g_screen, nullptr);
	}
}
//vertical Fence
static bool loadvFence(int FenceNum) {
	for (int i = 0; i < FenceNum; i++) {
		if (!vFence[i].LoadImage(g_screen, "..\\assets\\other\\FenceVertical.png")) {
			cout << "Khong the tai anh hang rao ngang thu" << i << endl;
			return false;
		}
		vFence[i].SetVertical();
	}
	return true;
}
static void loadVFenceBoundary(int FenceNum) {
	for (int i = 0; i < FenceNum; i++) {
		vFence[i].SetBoundary();
	}
}
static void vFenceShow(int FenceNum) {
	for (int i = 0; i < FenceNum; i++) {
		vFence[i].Render(g_screen, nullptr);
	}
}
//Tree
Tree trees[3];
static bool loadTrees(int treeNum) {
	for (int i = 0; i < treeNum; i++) {
		trees[i].setType(i + 1);
		if (!trees[i].loadTree(g_screen)) {
			return false;
		}
	}
	return true;
}
static void ShowTrees(int treeNum) {
	for (int i = 0; i < treeNum; i++) {
		trees[i].Render(g_screen, nullptr);
	}
}
//TrashCan
OrgTrashCan orgTrashCan;
RIOTrashCan rioTrashCan;
NRIOTrashCan nrioTrashCan;
ETrashCan eTrashCan;
//MapGrid
MapGrid mapGrid[6];
static void LoadMapGrid() {
	for (int i = 0; i < 6; i++) {
		mapGrid[i] = MapGrid(GRID_SIZE[i]);
	}
}
static int CheckGridObjectIn(SDL_Rect objRect) {
	if ((GRID1_SIZE.x <= objRect.x && objRect.x <= GRID1_SIZE.x + GRID1_SIZE.w) && (GRID1_SIZE.y <= objRect.y && objRect.y <= GRID1_SIZE.y + GRID1_SIZE.h)) {
		return 0;
	}
	else if ((GRID2_SIZE.x <= objRect.x && objRect.x <= GRID2_SIZE.x + GRID2_SIZE.w) && (GRID2_SIZE.y <= objRect.y && objRect.y <= GRID2_SIZE.y + GRID2_SIZE.h)) {
		return 1;
	}
	else if ((GRID3_SIZE.x <= objRect.x && objRect.x <= GRID3_SIZE.x + GRID3_SIZE.w) && (GRID3_SIZE.y <= objRect.y && objRect.y <= GRID3_SIZE.y + GRID3_SIZE.h)) {
		return 2;
	}
	else if ((GRID4_SIZE.x <= objRect.x && objRect.x <= GRID4_SIZE.x + GRID4_SIZE.w) && (GRID4_SIZE.y <= objRect.y && objRect.y <= GRID4_SIZE.y + GRID4_SIZE.h)) {
		return 3;
	}
	else if ((GRID5_SIZE.x <= objRect.x && objRect.x <= GRID5_SIZE.x + GRID5_SIZE.w) && (GRID5_SIZE.y <= objRect.y && objRect.y <= GRID5_SIZE.y + GRID5_SIZE.h)) {
		return 4;
	}
	else if ((GRID6_SIZE.x <= objRect.x && objRect.x <= GRID6_SIZE.x + GRID6_SIZE.w) && (GRID6_SIZE.y <= objRect.y && objRect.y <= GRID6_SIZE.y + GRID6_SIZE.h)) {
		return 5;
	}
	return -1;
}
bool check[6] = { false, false, false, false, false, false };
static void CheckObjectInAllGrid(SDL_Rect objRect) {
	for (int i = 0; i < 6; i++) {
		if (SDL_HasIntersection(&GRID_SIZE[i], &objRect)) {
			check[i] = true;
		}
		else {
			check[i] = false;
		}
	}
}
static void AddTrashToGrid(Trash* trash, int gridNumber) {
	if (gridNumber < 0 || gridNumber >= 6) {
		cout << "Gia tri khong hop le" << endl;
	}
	else {
		mapGrid[gridNumber].addTrashToMapGrid(trash);
	}
}

static void ShowTrashInAllGrid() {
	for (int i = 0; i < 6; i++) {
		mapGrid[i].showTrashInGrid(g_screen);
	}
}
//Trash
Trash bananaPeel[2];
Trash appleCore[2];
Trash bigStick[2];
Trash smallStick[2];
Trash redApple[2];
Trash purpleApple[2];
Trash can[2];
Trash glassBottle[2];
Trash papperBag[2];
Trash rubberDuck[2];
Trash rubberGloves[2];
Trash waterBottle[2];
Trash houseHoldTrash[2];
Trash insectSpray[2];
Trash plasticBag[2];
Trash sponge[2];
Trash battery[2];
Trash electricCircuit[2];
Trash electricWire[2];
Trash lightBulb[2];

bool static LoadAllTrash() {
	int grid_index;
	for (int i = 0; i < TRASH_QUANTITIES; i++) {
		bananaPeel[i] = Trash(TrashType::Organic, TrashSpecificType::BananaPeel);
		appleCore[i] = Trash(TrashType::Organic, TrashSpecificType::AppleCore);
		bigStick[i] = Trash(TrashType::Organic, TrashSpecificType::BigStick);
		smallStick[i] = Trash(TrashType::Organic, TrashSpecificType::SmallStick);
		redApple[i] = Trash(TrashType::Organic, TrashSpecificType::RedApple);
		purpleApple[i] = Trash(TrashType::Organic, TrashSpecificType::PurpleApple);
		can[i] = Trash(TrashType::Reclyable, TrashSpecificType::Can);
		glassBottle[i] = Trash(TrashType::Reclyable, TrashSpecificType::GlassBottle);
		papperBag[i] = Trash(TrashType::Reclyable, TrashSpecificType::PapperBag);
		rubberDuck[i] = Trash(TrashType::Reclyable, TrashSpecificType::RubberDuck);
		rubberGloves[i] = Trash(TrashType::Reclyable, TrashSpecificType::RubberGloves);
		waterBottle[i] = Trash(TrashType::Reclyable, TrashSpecificType::WaterBottle);
		houseHoldTrash[i] = Trash(TrashType::NonReclyable, TrashSpecificType::HouseHoldTrash);
		insectSpray[i] = Trash(TrashType::NonReclyable, TrashSpecificType::InsectSpray);
		plasticBag[i] = Trash(TrashType::NonReclyable, TrashSpecificType::PlasticBag);
		sponge[i] = Trash(TrashType::NonReclyable, TrashSpecificType::Sponge);
		battery[i] = Trash(TrashType::Electronic, TrashSpecificType::Battery);
		electricCircuit[i] = Trash(TrashType::Electronic, TrashSpecificType::ElectricCircuit);
		electricWire[i] = Trash(TrashType::Electronic, TrashSpecificType::ElectricWire);
		lightBulb[i] = Trash(TrashType::Electronic, TrashSpecificType::LightBulb);
		if (!bananaPeel[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(bananaPeel[i].GetRect());
			AddTrashToGrid(&bananaPeel[i], grid_index);
		}
		if (!appleCore[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(appleCore[i].GetRect());
			AddTrashToGrid(&appleCore[i], grid_index);
		}
		if (!bigStick[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(bigStick[i].GetRect());
			AddTrashToGrid(&bigStick[i], grid_index);
		}
		if (!smallStick[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(smallStick[i].GetRect());
			AddTrashToGrid(&smallStick[i], grid_index);
		}
		if (!redApple[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(redApple[i].GetRect());
			AddTrashToGrid(&redApple[i], grid_index);
		}
		if (!purpleApple[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(purpleApple[i].GetRect());
			AddTrashToGrid(&purpleApple[i], grid_index);
		}
		if (!can[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(can[i].GetRect());
			AddTrashToGrid(&can[i], grid_index);
		}
		if (!glassBottle[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(glassBottle[i].GetRect());
			AddTrashToGrid(&glassBottle[i], grid_index);
		}
		if (!papperBag[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(papperBag[i].GetRect());
			AddTrashToGrid(&papperBag[i], grid_index);
		}
		if (!rubberDuck[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(rubberDuck[i].GetRect());
			AddTrashToGrid(&rubberDuck[i], grid_index);
		}
		if (!rubberGloves[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(rubberGloves[i].GetRect());
			AddTrashToGrid(&rubberGloves[i], grid_index);
		}
		if (!waterBottle[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(waterBottle[i].GetRect());
			AddTrashToGrid(&waterBottle[i], grid_index);
		}
		if (!houseHoldTrash[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(houseHoldTrash[i].GetRect());
			AddTrashToGrid(&houseHoldTrash[i], grid_index);
		}
		if (!insectSpray[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(insectSpray[i].GetRect());
			AddTrashToGrid(&insectSpray[i], grid_index);
		}
		if (!plasticBag[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(plasticBag[i].GetRect());
			AddTrashToGrid(&plasticBag[i], grid_index);
		}
		if (!sponge[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(sponge[i].GetRect());
			AddTrashToGrid(&sponge[i], grid_index);
		}
		if (!battery[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(battery[i].GetRect());
			AddTrashToGrid(&battery[i], grid_index);
		}
		if (!electricCircuit[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(electricCircuit[i].GetRect());
			AddTrashToGrid(&electricCircuit[i], grid_index);
		}
		if (!electricWire[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(electricWire[i].GetRect());
			AddTrashToGrid(&electricWire[i], grid_index);
		}
		if (!lightBulb[i].LoadTrash(g_screen)) {
			return false;
		}
		else {
			grid_index = CheckGridObjectIn(lightBulb[i].GetRect());
			AddTrashToGrid(&lightBulb[i], grid_index);
		}
	}
	return true;
}
//temp
BaseObject horizontal;
BaseObject vertical;
BaseObject borderX1;
BaseObject borderX2;
BaseObject borderY1;
BaseObject borderY2;

BaseObject GRID_BORDER_Y;
BaseObject GRIDX1, GRIDX2, GRIDX3, GRIDX4;
static void RulerShow() {
	vertical.Render(g_screen, nullptr);
	horizontal.Render(g_screen, nullptr);
}
static void BorderUpdate() {
	SDL_Rect charRect = redhood.GetRealRect();
	borderX1.SetRect(charRect.x, charRect.y, charRect.w, 1);
	borderX2.SetRect(charRect.x, charRect.y + charRect.h, charRect.w, 1);
	borderY1.SetRect(charRect.x, charRect.y, 1, charRect.h);
	borderY2.SetRect(charRect.x + charRect.w, charRect.y, 1, charRect.h);
}
static void GRIDMAPBORDER() {
	GRID_BORDER_Y.SetRect(100, inventory.GetInventoryPresentY(), 100, 1);
	GRIDX1.SetRect(GRID1_SIZE.x + GRID1_SIZE.w, 0, 1, GRID1_SIZE.h);
	GRIDX2.SetRect(GRID2_SIZE.x + GRID1_SIZE.w, 0, 1, GRID2_SIZE.h);
	GRIDX3.SetRect(GRID4_SIZE.x + GRID4_SIZE.w, GRID4_SIZE.y, 1, GRID4_SIZE.h);
	GRIDX4.SetRect(GRID5_SIZE.x + GRID5_SIZE.w, GRID5_SIZE.y, 1, GRID5_SIZE.h);
}
static void BorderShow() {
	borderX1.Render(g_screen, nullptr);
	borderX2.Render(g_screen, nullptr);
	borderY1.Render(g_screen, nullptr);
	borderY2.Render(g_screen, nullptr);
	GRID_BORDER_Y.Render(g_screen, nullptr);
	GRIDX1.Render(g_screen, nullptr);
	GRIDX2.Render(g_screen, nullptr);
	GRIDX3.Render(g_screen, nullptr);
	GRIDX4.Render(g_screen, nullptr);
}
//airbone stack
AirboneStack airboneStack;

//combined function//
static void CharacterCollectTrash() {
	SDL_Rect charRect = redhood.GetRealRect();
	CheckObjectInAllGrid(charRect);
	for (int i = 0; i < 6; i++) {
		if (!check[i]) {
			continue;
		}
		int grid_index = i;
		Node* temp = mapGrid[grid_index].objectsList.pHead;
		if (grid_index == 0 || temp == nullptr || inventory.IsFull()) {
			continue;
		}
		while (temp != nullptr) {
			SDL_Rect trashRect = temp->trash->GetRect();
			if (SDL_HasIntersection(&charRect, &trashRect)) {
				inventory.AddTrashToInventory(redhood, temp->trash);
				if (!inventory.IsFull()) {
					mapGrid[grid_index].deleteTrashFromMapGrid(temp->trash);
				}
				return;
			}
			temp = temp->next;
		}
	}
}
static void CharacterThrowTrash() {
	Trash* tempTrash = inventory.GetTrashFromInventory(redhood);
	if (tempTrash == nullptr) {
		cout << "Khong co rac de nem" << endl;
		return;
	}
	airboneStack.GetInfomationForCal(redhood.GetRealRect());
	airboneStack.Push(tempTrash, redhood.IsFacingLeft());
	if (airboneStack.ReturnHead() == nullptr) {
		cout << "Loi" << endl;
	}
}
static void ThrowedTrashLimitRect(SDL_Rect trashRect) {

}
static void ProjectileMove(float time) {
	airboneStack.ProjectileCalXY(time, orgTrashCan, rioTrashCan, nrioTrashCan, eTrashCan, verticalHUD);
	//test
	Node* tempNode = airboneStack.ReturnHead();
	if (tempNode == nullptr) {
		return;
	}
}
static void TrashDeleteCheck() {
	Node* tempNode = airboneStack.ReturnHead();
	while (tempNode != nullptr) {
		if (reinterpret_cast<uintptr_t>(tempNode) == 0xDDDDDDDD || reinterpret_cast<uintptr_t>(tempNode) == 0x00000008) { std::cout << "Invalid tempNode detected!" << std::endl; return; }
		if (tempNode->trash == nullptr) {
			cout << "Khong co rac" << endl;
			return;
		}
		SDL_Rect trashRect = tempNode->trash->GetRect();
		if (trashRect.w == 0 && tempNode->isDisappeared) {
			airboneStack.GetTrashInStack(tempNode);
			return;
		}
		else if (trashRect.w != 0 && tempNode->isDisappeared) {
			Trash* tempTrash = airboneStack.GetTrashInStack(tempNode);
			int grid_index = CheckGridObjectIn(tempTrash->GetRect());
			AddTrashToGrid(tempTrash, grid_index);
		}
		tempNode = tempNode->next;
	}
}
static bool initAll() {
	if (
		!initGame() ||
		!loadBackground() ||
		!verticalHUD.LoadHUD(g_screen) ||
		!loadRedHood() ||
		!loadHouse() ||
		!loadFence(4) ||
		!loadvFence(3) ||
		!loadTrees(3) ||
		!orgTrashCan.LoadTrashCan(g_screen) ||
		!rioTrashCan.LoadTrashCan(g_screen) ||
		!nrioTrashCan.LoadTrashCan(g_screen) ||
		!eTrashCan.LoadTrashCan(g_screen) ||
		!LoadAllTrash() ||
		!inventoryBar.LoadInventoryBar(g_screen)
		) {
		return false;
	}
	return true;
}
static void SetUp() {
	house.SetRect(HOUSE_POS_X, HOUSE_POS_Y, HOUSE_WIDTH, HOUSE_HEIGHT);
	fence[0].SetRect(FENCE_NEAR_HOUSE_POS_X, FENCE1_NEAR_HOUSE_POS_Y, FENCE_WIDTH, FENCE_HEIGHT);
	fence[1].SetRect(FENCE_NEAR_HOUSE_POS_X, FENCE2_NEAR_HOUSE_POS_Y, FENCE_WIDTH, FENCE_HEIGHT);
	fence[2].SetRect(FENCE_NEAR_TREE_POS_X, FENCE1_NEAR_TREE_POS_Y, FENCE_WIDTH, FENCE_HEIGHT);
	fence[3].SetRect(FENCE_NEAR_TREE_POS_X, FENCE2_NEAR_TREE_POS_Y, FENCE_WIDTH, FENCE_HEIGHT);
	vFence[0].SetRect(VFENCE1_BELLOW_POS_X, VFENCE_BELLOW_POS_Y, VFENCE_WIDTH, VFENCE_HEIGHT);
	vFence[1].SetRect(VFENCE2_BELLOW_POS_X, VFENCE_BELLOW_POS_Y, VFENCE_WIDTH, VFENCE_HEIGHT);
	vFence[2].SetRect(VFENCE_NEAR_HOUSE_POS_X, VFENCE_NEAR_HOUSE_POS_Y, VFENCE_WIDTH, VFENCE_HEIGHT);
	loadVFenceBoundary(3);
	trees[0].SetRect(TOP_TREE_POS_X, TOP_TREE_POS_Y, TREE_WITDH, TREE_HEIGHT);
	trees[1].SetRect(MIDDLE_TREE_POS_X, MIDDLE_TREE_POS_Y, TREE_WITDH, TREE_HEIGHT);
	trees[2].SetRect(BOTTOM_TREE_POS_X, BOTTOM_TREE_POS_Y, LONG_TREE_WIDTH, LONG_TREE_HEIGHT);
}
int main(int argc, char* argv[]) {
	int timeCount = 0;
	timeCount++;
	float timeCal = (float)timeCount/100;
	//init
	LoadMapGrid();
	if (!initAll()) {
		return 0;
	}
	//Set Up
	SetUp();
	//test
	//inventory.AddTrashToInventory(redhood, mapGrid[3].objectsList.pHead->trash);
	horizontal.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\horizontal.png");
	vertical.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\vertical.png");
	borderX1.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
	borderX2.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
	borderY1.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderY.png");
	borderY2.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderY.png");
	GRID_BORDER_Y.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderY.png");
	GRIDX1.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
	GRIDX2.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
	GRIDX3.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
	GRIDX4.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\BorderX.png");
//running loop
	bool running = true;
	while (running) {
	GRIDMAPBORDER();
		SDL_PollEvent(&g_event);
		if (g_event.key.keysym.sym == SDLK_ESCAPE) {
			running = false;
		}
		if (g_event.type == SDL_QUIT) {
			running = false;
		}
		//Render
		SDL_RenderClear(g_screen);
		background.Render(g_screen, nullptr);
		house.Render(g_screen, nullptr);
		FenceShow(4);
		orgTrashCan.Render(g_screen, nullptr);
		nrioTrashCan.Render(g_screen, nullptr);
		ShowTrees(3);
		vFence[2].Render(g_screen, nullptr);
		redhood.HandleInput(g_screen, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S);
		//Fence Block
		for (int i = 0; i < 4; i++) {
			SDL_Rect temp = redhood.GetRealRect();
			int newX = temp.x + static_cast<int>(redhood.GetXVelocity());
			int newY = temp.y + static_cast<int>(redhood.GetYVelocity());
			if (redhood.CheckCollision(newX, temp.y, temp.w, temp.h, fence[i].GetRect())) {
				redhood.SetXVelocity(0);
			}
			if (redhood.CheckCollision(temp.x, newY, temp.w, temp.h, fence[i].GetRect())) {
				redhood.SetYVelocity(0);
			}
		}
		//VFenceBlock
		for (int i = 0; i < 3; i++) {
			SDL_Rect temp = redhood.GetRealRect();
			int newX = temp.x + static_cast<int>(redhood.GetXVelocity());
			int newY = temp.y + static_cast<int>(redhood.GetYVelocity());
			if (vFence[i].IsCollisionCheck(newX, temp.y, temp.w, temp.h)) {
				redhood.SetXVelocity(0);
			}
			if (vFence[i].IsCollisionCheck(temp.x, newY, temp.w, temp.h)) {
				redhood.SetYVelocity(0);
			}
		}
		//House Block
		SDL_Rect temp = redhood.GetRealRect();
		if (temp.x < 650 && temp.y < 395) {
			double yVelocity = redhood.GetYVelocity();
			if (yVelocity < 0) {
				redhood.SetYVelocity(0);
			}
		}
		//Tree block
		for (int i = 0; i < 3; i++) {
			SDL_Rect temp = redhood.GetRealRect();
			int newX = temp.x + static_cast<int>(redhood.GetXVelocity());
			int newY = temp.y + static_cast<int>(redhood.GetYVelocity());
			if (redhood.CheckCollision(newX, temp.y, temp.w, temp.h, trees[i].GetRect())) {
				redhood.SetXVelocity(0);
			}
			if(redhood.CheckCollision(temp.x, newY, temp.w, temp.h, trees[i].GetRect())){
				redhood.SetYVelocity(0);
			}
		}
		redhood.Move();
		SDL_Rect RedHoodPos = redhood.GetRect();
		if (RedHoodPos.y <= 702) {
			ShowTrashInAllGrid();
			redhood.ShowCharacter(g_screen);
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
		}
		else {
			ShowTrashInAllGrid();
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
			redhood.ShowCharacter(g_screen);
		}
		if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_e && !inventory.IsFull()) {
			CharacterCollectTrash();
		}
		if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_q && !inventory.IsEmpty()) {
			CharacterThrowTrash();
		}
		if (!airboneStack.isEmpty()) {
			ProjectileMove(timeCal);
		}
		if (!airboneStack.isEmpty()) {
			TrashDeleteCheck();
		}
		BorderUpdate();
		//BorderShow();
		//cap nhat stat
		inventoryBar.InventoryBarRender(g_screen);
		airboneStack.airboneStackShow(g_screen);
		verticalHUD.SetSpeed(redhood.GetSpeed());
		verticalHUD.RenderStat(g_screen, g_font);
		inventory.InventoryShow(g_screen);
		//RulerShow();
		SDL_RenderPresent(g_screen);
		redhood.ResetVelocity();
		if (timeCount > 100) {
			timeCount = 0;
		}
	}
	close();
	return 0;
}
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Character.h"
#include "House.h"
#include "Fence.h"
#include "Tree.h"
#include "TrashCan.h"
#include "HUD.h"
#include "Trash.h";

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
		if (!bananaPeel[i].LoadTrash(g_screen) ||
			!appleCore[i].LoadTrash(g_screen) ||
			!bigStick[i].LoadTrash(g_screen) ||
			!smallStick[i].LoadTrash(g_screen) ||
			!redApple[i].LoadTrash(g_screen) ||
			!can[i].LoadTrash(g_screen) ||
			!glassBottle[i].LoadTrash(g_screen) ||
			!papperBag[i].LoadTrash(g_screen) ||
			!rubberDuck[i].LoadTrash(g_screen) ||
			!rubberGloves[i].LoadTrash(g_screen) ||
			!waterBottle[i].LoadTrash(g_screen) ||
			!houseHoldTrash[i].LoadTrash(g_screen) ||
			!insectSpray[i].LoadTrash(g_screen) ||
			!plasticBag[i].LoadTrash(g_screen) ||
			!sponge[i].LoadTrash(g_screen) ||
			!battery[i].LoadTrash(g_screen) ||
			!electricCircuit[i].LoadTrash(g_screen) ||
			!electricWire[i].LoadTrash(g_screen) ||
			!lightBulb[i].LoadTrash(g_screen) ) {
			return false;
		}
	}
	return true;
}
void static ShowTrash() {
	for (int i = 0; i < TRASH_QUANTITIES; i++) {
		bananaPeel[i].Render(g_screen, nullptr);
		appleCore[i].Render(g_screen, nullptr);
		bigStick[i].Render(g_screen, nullptr);
		smallStick[i].Render(g_screen, nullptr);
		redApple[i].Render(g_screen, nullptr);
		can[i].Render(g_screen, nullptr);
		glassBottle[i].Render(g_screen, nullptr);
		papperBag[i].Render(g_screen, nullptr);
		rubberDuck[i].Render(g_screen, nullptr);
		rubberGloves[i].Render(g_screen, nullptr);
		waterBottle[i].Render(g_screen, nullptr);
		houseHoldTrash[i].Render(g_screen, nullptr);
		insectSpray[i].Render(g_screen, nullptr);
		plasticBag[i].Render(g_screen, nullptr);
		sponge[i].Render(g_screen, nullptr);
		battery[i].Render(g_screen, nullptr);
		electricCircuit[i].Render(g_screen, nullptr);
		electricWire[i].Render(g_screen, nullptr);
		lightBulb[i].Render(g_screen, nullptr);
	}
}
/*
BananaPeel, AppleCore, BigStick, SmallStick, RedApple, PurpleApple,
	Can, GlassBottle, PapperBag, RubberDuck, RubberGloves,WaterBottle,
	HouseHoldTrash, InsectSpray, PlasticBag, Sponge,
	Battery, ElectricCircuit, ElectricWire, LightBulb*/
BaseObject horizontal;
BaseObject vertical;
static void RulerShow() {
	vertical.Render(g_screen, nullptr);
	horizontal.Render(g_screen, nullptr);
}
int main(int argc, char* argv[]) {
//init
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
		return 0;
	}
//Set Up
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
	//test
	horizontal.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\horizontal.png");
	vertical.LoadImage(g_screen, "D:\\GameProject\\OOPFinal\\assets\\vertical.png");

//running loop
	bool running = true;
	while (running) {
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
			ShowTrash();
			redhood.ShowCharacter(g_screen);
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
		}
		else {
			ShowTrash();
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
			redhood.ShowCharacter(g_screen);
		}
		//cap nhat stat
		inventoryBar.InventoryBarRender(g_screen);
		verticalHUD.SetSpeed(redhood.GetSpeed());
		verticalHUD.RenderStat(g_screen, g_font);
		SDL_RenderPresent(g_screen);
		redhood.ResetVelocity();
	}
	close();
	return 0;
}
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Character.h"
#include "House.h"
#include "Fence.h"
#include "Tree.h"
#include "TrashCan.h"
#include "HUD.h"

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
		!eTrashCan.LoadTrashCan(g_screen)
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
			redhood.ShowCharacter(g_screen);
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
		}
		else {
			vFenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
			redhood.ShowCharacter(g_screen);
		}
		//cap nhat stat
		verticalHUD.SetSpeed(redhood.GetSpeed());
		verticalHUD.RenderStat(g_screen, g_font);
		SDL_RenderPresent(g_screen);
		redhood.ResetVelocity();
	}
	close();
	return 0;
}
#include "BaseFunction.h"
#include "BaseObject.h"
#include "Character.h"
#include "House.h"
#include "Frence.h"
#include "Tree.h"
#include "TrashCan.h"

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
	return true;
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
	house.SetRect(128, 20, 599, 575);
	return true;
}
//frence
Frence frence[4];
Frence vFrence[3];
//Horizontal Frence
static bool loadFrence(int frenceNum) {
	for (int i = 0; i < frenceNum; i++) {
		if (!frence[i].LoadImage(g_screen, "..\\assets\\other\\FrenceHorizontal.png")) {
			cout << "Khong the tai anh hang rao thu" << i << endl;
			return false;
		}
	}
	frence[0].SetRect(730, -30, 50, 265);
	frence[1].SetRect(730, 235, 50, 265);
	frence[2].SetRect(1376, 64, 50, 265);
	frence[3].SetRect(1376, 600, 50, 265);
	return true;
}
static void frenceShow(int frenceNum) {
	for (int i = 0; i < frenceNum; i++) {
		frence[i].Render(g_screen, nullptr);
	}
}
//vertical Frence
static bool loadvFrence(int frenceNum) {
	for (int i = 0; i < frenceNum; i++) {
		if (!vFrence[i].LoadImage(g_screen, "..\\assets\\other\\FrenceVertical.png")) {
			cout << "Khong the tai anh hang rao ngang thu" << i << endl;
			return false;
		}
		vFrence[i].SetVertical();
	}
	vFrence[0].SetRect(192, 790, 304, 121);
	vFrence[1].SetRect(832, 790, 304, 121);
	vFrence[2].SetRect(-152, 466, 304, 121);
}
static void loadVFrenceBoundary(int frenceNum) {
	for (int i = 0; i < frenceNum; i++) {
		vFrence[i].SetBoundary();
	}
}
static void vFrenceShow(int frenceNum) {
	for (int i = 0; i < frenceNum; i++) {
		vFrence[i].Render(g_screen, nullptr);
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
	trees[0].SetRect(1690, 32, 256, 256);
	trees[1].SetRect(1690, 312, 256, 256);
	trees[2].SetRect(1690, 596, 230, 380);
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


//End
static void close() {
	background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = nullptr;
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	//init
	/*if (!initGame()) {
		return 0;
	}
	if (!loadBackground()) {
		return 0;
	}
	if (!loadRedHood()) {
		return 0;
	}
	if (!loadHouse()) {
		return 0;
	}
	if (!loadFrence(4)) {
		return 0;
	}
	if (!loadvFrence(3)) {
		return 0;
	}
	loadVFrenceBoundary(3);
	if (!loadTrees(3)) {
		return 0;
	}
	if (!orgTrashCan.LoadTrashCan(g_screen)) {
		return 0;
	}*/
	if (
		!initGame() ||
		!loadBackground() ||
		!loadRedHood() ||
		!loadHouse() ||
		!loadFrence(4) ||
		!loadvFrence(3) ||
		!loadTrees(3) ||
		!orgTrashCan.LoadTrashCan(g_screen) ||
		!rioTrashCan.LoadTrashCan(g_screen) ||
		!nrioTrashCan.LoadTrashCan(g_screen) ||
		!eTrashCan.LoadTrashCan(g_screen)
		) {
		return 0;
	}
	loadVFrenceBoundary(3);
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
		frenceShow(4);
		orgTrashCan.Render(g_screen, nullptr);
		nrioTrashCan.Render(g_screen, nullptr);
		ShowTrees(3);
		vFrence[2].Render(g_screen, nullptr);
		//showItem();
		redhood.HandleInput(g_screen, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S);
		//Frence Block
		for (int i = 0; i < 4; i++) {
			SDL_Rect temp = redhood.GetRealRect();
			int newX = temp.x + static_cast<int>(redhood.GetXVelocity());
			int newY = temp.y + static_cast<int>(redhood.GetYVelocity());
			if (redhood.CheckCollision(newX, temp.y, temp.w, temp.h, frence[i].GetRect())) {
				redhood.SetXVelocity(0);
			}
			if (redhood.CheckCollision(temp.x, newY, temp.w, temp.h, frence[i].GetRect())) {
				redhood.SetYVelocity(0);
			}
		}
		//VfrenceBlock
		for (int i = 0; i < 3; i++) {
			SDL_Rect temp = redhood.GetRealRect();
			int newX = temp.x + static_cast<int>(redhood.GetXVelocity());
			int newY = temp.y + static_cast<int>(redhood.GetYVelocity());
			if (vFrence[i].IsCollisionCheck(newX, temp.y, temp.w, temp.h)) {
				redhood.SetXVelocity(0);
			}
			if (vFrence[i].IsCollisionCheck(temp.x, newY, temp.w, temp.h)) {
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
			vFrenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
		}
		else {
			vFrenceShow(2);
			rioTrashCan.Render(g_screen, nullptr);
			eTrashCan.Render(g_screen, nullptr);
			redhood.ShowCharacter(g_screen);
		}
		SDL_RenderPresent(g_screen);
		redhood.ResetVelocity();
	}
	close();
	return 0;
}
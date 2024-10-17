#include "Tree.h"

Tree::Tree() {
	for (int i = 0; i < 3; i++) {
		type[i] = false;
	}
}
void Tree::setType(int type) {
	this->type[type - 1] = true;
}

bool Tree::loadTree(SDL_Renderer* screen) {
	if (type[0] == true) {
		if (!this->LoadImage(screen, "..\\assets\\other\\tree1.png")) {
			return false;
		}
	}
	else if (type[1] == true) {
		if (!this->LoadImage(screen, "..\\assets\\other\\tree2.png")) {
			return false;
		}
	}
	else {
		if (!this->LoadImage(screen, "..\\assets\\other\\tree3.png")) {
			return false;
		}
	}
	return true;
}
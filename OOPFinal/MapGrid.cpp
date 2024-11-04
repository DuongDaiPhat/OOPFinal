#include "MapGrid.h"

MapGrid::MapGrid() {
	InitList(objectsList);
	mapGridSize = { 0,0,0,0 };
}
MapGrid::~MapGrid() {
	DeleteList(objectsList);
	mapGridSize = { 0,0,0,0 };
}
MapGrid::MapGrid(SDL_Rect rect) {
	InitList(objectsList);
	mapGridSize = rect;
}
SDL_Rect MapGrid::getMapGridRect() const {
	return mapGridSize;
}
void MapGrid::addTrashToMapGrid(Trash* trash) {
	AddNode(objectsList, trash);
}
void MapGrid::deleteTrashFromMapGrid(Trash* trash) {
	DeleteNode(objectsList, trash);
}
void MapGrid::operator=(MapGrid grid2) {
	this->mapGridSize = grid2.mapGridSize;
	this->objectsList = grid2.objectsList;
}
void MapGrid::showTrashInGrid(SDL_Renderer* screen) const{
	if (objectsList.pHead == nullptr) {
		return;
	}
	Node* temp = objectsList.pHead;
	while (temp != nullptr) {
		temp->trash->Render(screen, nullptr);
		temp = temp->next;
	}
}
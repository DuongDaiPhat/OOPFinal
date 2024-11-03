#include "MapGrid.h"

static void initList(List& list) {
	list.pHead = list.pTail = nullptr;
}
static void deleteList(List& list) {
	while (list.pHead != nullptr) {
		Node* del = list.pHead;
		list.pHead = list.pHead->next;
		delete del;
		del = nullptr;
	}
}
static Node* createNode(Trash *trash) {
	Node* temp = new Node;
	if (temp == nullptr) {
		cout << "Khong du bo nho" << endl;
		return nullptr;
	}
	temp->trash = trash;
	temp->next = nullptr;
	return temp;
}
void addNode(List& list, Trash *trash) {
	Node* temp = createNode(trash);
	if (list.pHead == nullptr || list.pTail == nullptr) {
		list.pHead = temp;
		list.pTail = temp;
	}
	else {
		list.pTail->next = temp;
		list.pTail = temp;
	}
}
static void deleteNode(List& list, Trash* trash) {
	if (list.pHead == nullptr) return;

	if (list.pHead->trash == trash) {
		Node* del = list.pHead;
		list.pHead = list.pHead->next;
		delete del;
		if (list.pHead == nullptr)
			list.pTail = nullptr;
		return;
	}
	else {
		Node* prevNode = list.pHead;
		Node* presentNode = list.pHead->next;
		while (presentNode != nullptr) {
			if (presentNode->trash == trash) {
				Node* del = presentNode;
				prevNode->next = presentNode->next;
				delete del;
				del = nullptr;
				break;
			}
			prevNode = presentNode;
			presentNode = presentNode->next;
		}
	}
}
MapGrid::MapGrid() {
	initList(objectsList);
	mapGridSize = { 0,0,0,0 };
}
MapGrid::~MapGrid() {
	deleteList(objectsList);
	mapGridSize = { 0,0,0,0 };
}
MapGrid::MapGrid(SDL_Rect rect) {
	initList(objectsList);
	mapGridSize = rect;
}
SDL_Rect MapGrid::getMapGridRect() const {
	return mapGridSize;
}
void MapGrid::addTrashToMapGrid(Trash* trash) {
	addNode(objectsList, trash);
}
void MapGrid::deleteTrashFromMapGrid(Trash* trash) {
	deleteNode(objectsList, trash);
}
void MapGrid::operator=(MapGrid grid2) {
	this->mapGridSize = grid2.mapGridSize;
	this->objectsList = grid2.objectsList;
}
void MapGrid::showTrashInGrid(SDL_Renderer* screen) {
	if (objectsList.pHead == nullptr) {
		return;
	}
	Node* temp = objectsList.pHead;
	while (temp != nullptr) {
		temp->trash->Render(screen, nullptr);
		temp = temp->next;
	}
}
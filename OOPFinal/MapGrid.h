#pragma once
#include "BaseObject.h"
#include "Trash.h"

typedef struct Node {
	Trash* trash;
	Node* next;
}Node;
typedef struct List {
	Node* pHead;
	Node* pTail;
}List;

class MapGrid {
private:
	SDL_Rect mapGridSize;
public:
	List objectsList;
	MapGrid();
	~MapGrid();
	MapGrid(SDL_Rect rect);
	SDL_Rect getMapGridRect() const;
	void addTrashToMapGrid(Trash* trash);
	void deleteTrashFromMapGrid(Trash* trash);
	void showTrashInGrid(SDL_Renderer* screen);
	void operator=(MapGrid grid2);
	friend void addNode(List& objectList, Trash* trash);
};
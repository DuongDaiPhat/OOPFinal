#pragma once
#include "BaseObject.h"
#include "Trash.h"
#include "DataStructure.h"

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
	void showTrashInGrid(SDL_Renderer* screen) const;
	void operator=(MapGrid grid2);
	friend void AddNode(List& objectList, Trash* trash);
};
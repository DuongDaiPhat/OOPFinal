#pragma once
#include "BaseObject.h"
//Con trỏ bàn phím

extern const Uint8* pkey;
class AirboneStack;
typedef struct input {
	bool idle;
	bool goUp;
	bool goDown;
	bool goLeft;
	bool goRight;
}input;
class Character :public BaseObject {
protected:
	int frameCount;
	int frameNumber;
	int frameWidth;
	int frameHeight;
	SDL_Rect* actionFrameClip;
	double xVelocity;
	double yVelocity;
	int charSpeed;
	input inputType;
	bool isFacingLeft;
public:
	Character();
	~Character();
	int GetSpeed() const;
	void SetSpeed(int speed);
	bool LoadCharacterImage(SDL_Renderer* screen, const string file_path);
	bool ShowCharacter(SDL_Renderer* screen);
	void HandleInput(SDL_Renderer* screen,SDL_Scancode left, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down);
	void SetClips();
	bool IsFacingLeft() const;
	double GetXVelocity() const;
	double GetYVelocity() const;
	void SetXVelocity(int Velocity);
	void SetYVelocity(int Velocity);
	void ResetVelocity();
	void SetSpawn(int x, int y);
	void Move();
	SDL_Rect GetRealRect();
	bool CheckCollision(int newX, int newY,int w, int h, SDL_Rect otherRect);
	friend class Inventory;
	friend class AirboneStack;
};
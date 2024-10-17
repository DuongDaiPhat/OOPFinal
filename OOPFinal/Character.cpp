#include "Character.h"
#include "BaseFunction.h"
#include "math.h"

static const Uint8* pkey = SDL_GetKeyboardState(NULL);
Character::Character() {
	frameCount = 0;
	frameNumber = 0;
	frameWidth = 0;
	frameHeight = 0;
	xVelocity = 0;
	yVelocity = 0;
	inputType.doNothing = 1;
	inputType.goDown = 0;
	inputType.goLeft = 0;
	inputType.goRight = 0;
	inputType.goUp = 0;
	objectTexture = NULL;
	objectRect = { 0,0,0,0 };
	charSpeed = 5;
}
Character::~Character() {
	SDL_DestroyTexture(objectTexture);
	objectTexture = NULL;
	delete[] actionFrameClip;
}

int Character::GetSpeed() {
	return charSpeed;
}

void Character::SetSpeed(int speed) {
	charSpeed = speed;
}
bool Character::LoadCharacterImage(SDL_Renderer* screen, const string file_path) {
	bool check = BaseObject::LoadImage(screen, file_path);
	if (!check) {
		cout << "Khong the tai hinh anh nhan vat" << endl;
		return false;
	}
	frameHeight = 40;
	frameWidth = 25;
	frameNumber = objectRect.w / 25;
	if (frameNumber > 0) {
		actionFrameClip = new SDL_Rect[frameNumber];
		this->SetClips();
	}
	return true;
}
void Character::SetClips() {
	for (int i = 0; i < frameNumber; i++) {
		actionFrameClip[i].x = i * frameWidth;
		actionFrameClip[i].y = 0;
		actionFrameClip[i].w = frameWidth;
		actionFrameClip[i].h = frameHeight;
	}
}
void Character::HandleInput(SDL_Renderer* screen,SDL_Scancode left, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down) {
	inputType.doNothing = 1;
	if (pkey[left]) {
		if (inputType.goLeft == 0) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodRunAnimation.png");
		}
		inputType.goRight = 0;
		xVelocity -= charSpeed;
		inputType.goLeft = 1;
		inputType.doNothing = 0;
	}
	if (pkey[right]) {
		if (inputType.goRight == 0) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodRunAnimation.png");
		}
		inputType.goLeft = 0;
		xVelocity += charSpeed;
		inputType.goRight = 1;
		inputType.doNothing = 0;
	}
	if (pkey[up]) {
		if (inputType.goUp == 0) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodRunAnimation.png");
		}
		inputType.goDown = 0;
		yVelocity -= charSpeed;
		inputType.goUp = 1;
		inputType.doNothing = 0;
	}
	if (pkey[down]) {
		if (inputType.goDown == 0) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodRunAnimation.png");
		}
		inputType.goUp = 0;
		yVelocity += charSpeed;
		inputType.goDown = 1;
		inputType.doNothing = 0;
	}
	if (inputType.doNothing) {
		if (inputType.goRight == 1) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodIdleRight.png");
		}
		else if (inputType.goLeft == 1) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodIdleLeft.png");
		}
		else if (inputType.goDown == 1) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodIdleRight.png");
		}
		else if (inputType.goUp == 1) {
			LoadCharacterImage(screen, "..\\assets\\characterSpriteSheet\\RedHoodIdleRight.png");
		}
	}
	
	if (xVelocity != 0 && yVelocity != 0) {
		xVelocity /= sqrt(2);
		yVelocity /= sqrt(2);
	}
	else if (objectRect.y < -50) {
		objectRect.y = -50;
	}
	if (!pkey[left]) {
		inputType.goLeft = 0;
	}
	if (!pkey[right]) {
		inputType.goRight = 0;
	}
	if (!pkey[up]) {
		inputType.goUp = 0;
	}
	if (!pkey[down]) {
		inputType.goDown = 0;
	}
}

bool Character::ShowCharacter(SDL_Renderer* screen) {
	static int animationDelay = 0;
	if (inputType.goDown == 1 || inputType.goLeft == 1 || inputType.goRight == 1 || inputType.goUp == 1) {
		animationDelay++;
		if (animationDelay >= 5) {
			frameCount++;
			animationDelay = 0;
		}
	}
	else if (inputType.doNothing == 1) {
		animationDelay++;
		if (animationDelay >= 8) {
			frameCount++;
			animationDelay = 0;
		}
	}
	else {
		frameCount = 0;
	}
	if (frameCount >= frameNumber) {
		frameCount = 0;
	}
	SDL_Rect* currentClip = &actionFrameClip[frameCount];
	SDL_Rect renderQuad = { objectRect.x, objectRect.y, 125, 200};
	if (inputType.goRight == 1) {
		SDL_RenderCopy(screen, objectTexture, currentClip, &renderQuad);
		cout << "objectRect: x=" << objectRect.x << ", y=" << objectRect.y << ", w=" << objectRect.w << ", h=" << objectRect.h << endl;
		cout << "currentClip x=" << currentClip->x << ", y = " << currentClip->y << ", w = " << currentClip->w << ", h = " << currentClip->h << endl;
	}
	else if (inputType.goLeft == 1) {
		SDL_RenderCopyEx(screen, objectTexture, currentClip, &renderQuad,0,NULL,SDL_FLIP_HORIZONTAL);
		cout << "objectRect: x=" << objectRect.x << ", y=" << objectRect.y << ", w=" << objectRect.w << ", h=" << objectRect.h << endl;
		cout << "currentClip x=" << currentClip->x << ", y = " << currentClip->y << ", w = " << currentClip->w << ", h = " << currentClip->h << endl;
	}
	else {
		SDL_RenderCopy(screen, objectTexture, currentClip, &renderQuad);
	}
	return true;
}

double Character::GetXVelocity() {
	return xVelocity;
}
double Character::GetYVelocity() {
	return yVelocity;
}
void Character::SetXVelocity(int Velocity) {
	xVelocity = Velocity;
}
void Character::SetYVelocity(int Velocity) {
	yVelocity = Velocity;
}
void Character::ResetVelocity() {
	xVelocity = 0;
	yVelocity = 0;
}
void Character::SetSpawn(int x, int y) {
	objectRect.x = x;
	objectRect.y = y;
}
void Character::Move() {
	objectRect.x += static_cast<int>(xVelocity);
	if (objectRect.x > SCREEN_WIDTH - frameWidth - 100) {
		objectRect.x = SCREEN_WIDTH - frameWidth - 100;
	}
	else if (objectRect.x < 0) {
		objectRect.x = 0;
	}
	objectRect.y += static_cast<int>(yVelocity);
	if (objectRect.y > SCREEN_HEIGHT - frameHeight - 150) {
		objectRect.y = SCREEN_HEIGHT - frameHeight - 150;
	}
	else if (objectRect.y < -50) {
		objectRect.y = -50;
	}
}
SDL_Rect Character::GetRealRect() {
	SDL_Rect realRect = { objectRect.x, objectRect.y + 30,100,175};
	return realRect;
}

bool Character::CheckCollision(int newX, int newY, int w,int h, SDL_Rect otherRect) {
	SDL_Rect check = { newX, newY, w, h };
	return SDL_HasIntersection(&check, &otherRect);
}
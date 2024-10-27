#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

//Tạo biến con trỏ vào khung cửa sổ
static SDL_Window *g_window;
//Tạo biến con trỏ vào màn hình
static SDL_Renderer* g_screen;
//Tạo biến thu thập sự kiện người chơi
static SDL_Event g_event;

//Thông số cơ bản
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


//Kích thước thùng rác
const int TRASH_CAN_WIDTH = 130;
const int TRASH_CAN_HEIGHT = 160;
//Vị trí thùng rác
const int ORG_TRASH_CAN_POS_X = 1335;
const int ORG_TRASH_CAN_POS_Y = 300;
const int E_TRASH_CAN_POS_X = 278;
const int E_TRASH_CAN_POS_Y = 767;
const int RIO_TRASH_CAN_POS_X = 920;
const int RIO_TRASH_CAN_POS_Y =  767;
const int NRIO_TRASH_CAN_POS_X = 695;
const int NRIO_TRASH_CAN_POS_Y = 470;


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
//font
extern TTF_Font* g_font;
//Thông số cơ bản
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
//Màu chữ
const int TEXT_COLOR_R = 0;
const int TEXT_COLOR_G = 0;
const int TEXT_COLOR_B = 0;
const int TEXT_TRANSPARENCY = 255;
//Cỡ chữ
const int TEXT_SIZE = 50;
//vi tri speed text
const int SPEED_TEXT_POS_X = 275;
const int SPEED_TEXT_POS_Y = 45;
//vi tri point text
const int POINT_TEXT_POS_X = 255;
const int POINT_TEXT_POS_Y = 5;
//kich thuoc Vertical HUD
const int VERTICAL_HUD_POS_X = 0;
const int VERTICAL_HUD_POS_Y = 0;
const int VERTICAL_HUD_WEIGHT = 480;
const int VERTICAL_HUD_HEIGHT = 120;
//kich thuoc Inventory Bar
const int INVENTORYBAR_POSX = 0;
const int INVENTORYBAR_POSY = 120;
const int INVENTORYBAR_WIDTH = 100;
const int INVENTORYBAR_HEIGHT = 320;
//kich thuoc balo icon
const int BALOICON_POSX = 25;
const int BALOICON_POSY = 140;
const int BALOICON_WIDTH = 60;
const int BALOICON_HEIGHT = 60;
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
//Kích thước và vị trí nhà
const int HOUSE_POS_X = 128;
const int HOUSE_POS_Y = -64;
const int HOUSE_WIDTH = 599;
const int HOUSE_HEIGHT = 678;
//kich thuoc va vi tri hang rao doc
const int FENCE_WIDTH = 50;
const int FENCE_HEIGHT = 265;
const int FENCE_NEAR_HOUSE_POS_X = 730;
const int FENCE1_NEAR_HOUSE_POS_Y = -30;
const int FENCE2_NEAR_HOUSE_POS_Y = 235;
const int FENCE_NEAR_TREE_POS_X = 1376;
const int FENCE1_NEAR_TREE_POS_Y = 64;
const int FENCE2_NEAR_TREE_POS_Y = 600;
//kich thuoc va vi tri hang rao ngang
const int VFENCE_WIDTH = 304;
const int VFENCE_HEIGHT = 121;
const int VFENCE_NEAR_HOUSE_POS_X = -152;
const int VFENCE_NEAR_HOUSE_POS_Y = 466;
const int VFENCE_BELLOW_POS_Y = 790;
const int VFENCE1_BELLOW_POS_X = 192;
const int VFENCE2_BELLOW_POS_X = 832;
//kich thuoc va vi tri cay.
const int TREE_WITDH = 256;
const int TREE_HEIGHT = 256;
const int LONG_TREE_WIDTH = 230;
const int LONG_TREE_HEIGHT = 380;
const int TOP_TREE_POS_X = 1690;
const int TOP_TREE_POS_Y = 32;
const int MIDDLE_TREE_POS_X = 1690;
const int MIDDLE_TREE_POS_Y = 312;
const int BOTTOM_TREE_POS_X = 1690;
const int BOTTOM_TREE_POS_Y = 596;
//So luong rac tren moi loai rac
const int TRASH_QUANTITIES = 2;
//MapGrid Size
const SDL_Rect GRID1_SIZE = { 0,0,832,576 };
const SDL_Rect GRID2_SIZE = { 833,0, 511, 576 };
const SDL_Rect GRID3_SIZE = { 1345, 0, 383, 576 };
const SDL_Rect GRID4_SIZE = { 0, 577, 768, 504 };
const SDL_Rect GRID5_SIZE = { 769, 577, 575, 504 };
const SDL_Rect GRID6_SIZE = { 1345, 577, 383, 504 };
const SDL_Rect GRID_SIZE[6] = { GRID1_SIZE,GRID2_SIZE,GRID3_SIZE, GRID4_SIZE, GRID5_SIZE, GRID6_SIZE};

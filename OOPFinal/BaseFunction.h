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


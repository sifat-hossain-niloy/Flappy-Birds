#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>
#include "defs.h"
using namespace std;

typedef struct {
	int x;
	int y;
	int w;
	int h;
} Wall;

Wall wallx[5] = {{SCREEN_WIDTH + 20,0,40,170},{SCREEN_WIDTH + 220,SCREEN_HEIGHT - 130,35,130},{SCREEN_WIDTH + 430,SCREEN_HEIGHT - 200,50,200},{SCREEN_WIDTH + 590,60,27,60},{SCREEN_WIDTH + 590, 60, 27,60},{SCREEN_WIDTH + 300,0,50,140}};
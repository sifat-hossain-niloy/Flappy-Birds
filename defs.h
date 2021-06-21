#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

int x = -1;
//Screen dimension constants
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 724;

//Button constants
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 100;
const int TOTAL_BUTTONS = 4;

const int parts = 1;
const int foody = 1;

int positionx, positiony;

Uint64 startTime = 0;

//In memory text stream

bool quit = false;
long long int score;
int life, checklife, noncollied;
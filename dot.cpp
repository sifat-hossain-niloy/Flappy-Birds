#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>

#include "texture.h"
#include "defs.h"
using namespace std;


bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA + 20 >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB + 7)
	{
		return false;
	}

	if ((leftA + 40) >= rightB)
	{
		return false;
	}

	return true;
}


Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_QUIT)
	{
		quit = true;
	}
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
            case SDLK_UP:
                mVelY -= DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY += DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX += DOT_VEL;
                break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
            case SDLK_UP:
                mVelY += DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY -= DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX += DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX -= DOT_VEL;
                break;
		}
	}
}
void Dot::move(SDL_Rect &wall)
{
	static int r = 0;
	checklife = 0;
	if (r == 0)
	{
		//Move the dot left or right
		mPosX += mVelX;
		mCollider.x = mPosX;

		//Move the dot up or down
		mPosY += mVelY;
		mCollider.y = mPosY;

	}
	//If the dot collided or went too far to the left or right
	if (r < 5)
	{
		if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
		{
			//Move back
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}

		//If the dot collided or went too far up or down
		if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
		{
			//Move back
			mPosY -= mVelY;
			mCollider.y = mPosY;
		}
		if (checkCollision(mCollider, wall) && r != noncollied)
		{
			SDL_Delay(1000);
			life--;
			mPosX = 0;
			mPosY = 200;
			wall.h = 0;
			wall.w = 0;
			noncollied = r;
		}
	}

	else if (r == 5)
	{
		if (checkCollision(mCollider, wall))
		{
			gfoodyClips[0].w = 0;
			gfoodyClips[0].h = 0;
			score += 500;
            Mix_PlayChannel(-1, gScratch, 0);
		}
	}
	else if (r == 6)
	{
		if (checkCollision(mCollider, wall))
		{
			gSpriteClips[0].w = 0;
			gSpriteClips[0].h = 0;
			checklife++;
		}
	}
	r++;
	if (r == 7)r = 0;
}

void Dot::render()
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY);
}
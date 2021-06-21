#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>
#include "defs.h"
#include "texture.cpp"
#include "init.cpp"
#include "dot.cpp"
#include "scoreboard.cpp"


using namespace std;

int main(int argc, char *args[])
{

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
        else
		{
			//if(x==-1)
			while (x)
			{
			    SDL_Event m;
			    kol=0;
				x = loadmenu();

				if (x == 1 && kol==1)
				{
                            SDL_Event e;
                            //Set text color as black
                            SDL_Color textColor = {206, 255, 243, 255};

                            //The dot that will be moving around on the screen
                            Dot dot;

                            double scrollingOffset = 0;
                            int scroll = 0, changecolori[6], changecolorj[6], changecolork[6];
                            double loveWidth = 900, loveHeight = 350;
                            double foodWidth = SCREEN_WIDTH + 350, foodHeight = 250;

                            memset(changecolori, 0, sizeof(changecolori));
                            memset(changecolorj, 0, sizeof(changecolorj));
                            memset(changecolork, 0, sizeof(changecolork));
                            double scrollspeed = 2;

                            wall[0].x = SCREEN_WIDTH + 20;
                            wall[0].y = 0;
                            wall[0].w = 40;
                            wall[0].h = 170;

                            wall[1].x = SCREEN_WIDTH + 220;
							wall[1].y = SCREEN_HEIGHT - wall[1].h;
                            wall[1].w = 35;
                            wall[1].h = 130;

                            wall[2].x = SCREEN_WIDTH + 430;
							wall[2].y = SCREEN_HEIGHT - wall[2].h;
                            wall[2].w = 50;
                            wall[2].h = 200;

                            wall[3].x = SCREEN_WIDTH + 590;
                            wall[3].y = 60;
                            wall[3].w = 27;
                            wall[3].h = 60;

                            wall[4].x = SCREEN_WIDTH + 300;
                            wall[4].y = 0;
                            wall[4].w = 50;
                            wall[4].h = 140;

                            int liferecheck = 0;
                            int frame = 0;
                            dot.mPosX = dot.mPosY = dot.mVelX = dot.mVelY = 0;
                            score = 0;
                            life = 0, checklife = 0, noncollied = -1;
                            quit=false;
                            while (!quit)
                            {
                                while (SDL_PollEvent(&e))
                                {
                                    if (e.type == SDL_QUIT)
                                    {
                                        quit = true;
                                    }
                                    dot.handleEvent(e);
                                }
								
								for(int now = 0 ; now < 5 ; now++)
								{
									dot.move(wall[now]);
								}
                                
                                dot.move(food[0]);
                                dot.move(love[0]);

                                if (checklife > 0 && liferecheck == 0)
                                {
                                    life++;
                                    liferecheck = 1;
                                }

                                if (life < 0)
                                {
                                    loadscoreboard();
                                    quit = true;
                                    x=5;
									Mix_HaltMusic();
                                    break;
                                }
                                //Scroll background
                                scrollingOffset -= scrollspeed;

								for(int now = 0 ; now < 5 ; now++)
								{
									 wall[now].x -= scrollspeed;
								}
                               
                                foodWidth -= scrollspeed;
                                loveWidth -= scrollspeed;

                                if (loveWidth <= -20)
                                {
                                    loveWidth = 1800;
                                    loveHeight += 100;
                                    gSpriteClips[0].w = 20;
                                    gSpriteClips[0].h = 20;
                                    if (loveHeight >= 390)
                                        loveHeight = 80;
                                }

                                if (foodWidth <= -30)
                                {
                                    foodWidth = 1200;
                                    if (foodHeight >= 80)
                                        foodHeight -= 30;
                                    else
                                        foodHeight = 350;
                                    gfoodyClips[0].w = 35;
                                    gfoodyClips[0].h = 35;
                                }
                                if (scrollingOffset < -gBGTexture.getWidth())
                                {
                                    scrollingOffset = 0;
                                    scroll++;
                                    liferecheck = 0;
                                }

                                for (int i = 0; i <= 4; i++)
                                {

                                    if (wall[i].x <= -70)
                                    {
                                        if (i == noncollied)
                                            noncollied = -1;
                                        if (i != 5)
                                            wall[i].x = SCREEN_WIDTH;
                                        else
                                        {
                                            wall[i].x = SCREEN_WIDTH + 1400;
                                            wall[i].h = 14;
                                            wall[i].w = 14;
                                        }
                                        if (i == 3)
                                        {
                                            wall[i].y -= 60;
                                            if (wall[i].w < 70)
                                                wall[i].w += 3;
                                            else
                                                wall[i].w = 40;
                                            if (wall[i].h > 60)
                                                wall[i].h -= 40;
                                            else
                                                wall[i].h = 150;
                                            if (wall[3].y <= 0)
                                                wall[3].y = 250;
                                        }

                                        if (i % 2 == 0)
                                        {
                                            if (wall[i].w < 70)
                                                wall[i].w += 3;
                                            else
                                                wall[i].w = 30;
                                            if (wall[i].h > 60)
                                                wall[i].h -= 40;
                                            else
                                                wall[i].h = 200;
                                            if (i == 2)
                                                wall[i].y = SCREEN_HEIGHT - wall[i].h;
                                        }
                                        else if (i == 1)
                                        {
                                            if (wall[i].w < 60)
                                                wall[i].w += 3;
                                            else
                                                wall[i].w = 40;
                                            if (wall[i].h > 60)
                                                wall[i].h -= 40;
                                            else
                                                wall[i].h = 200;
                                            wall[i].y = SCREEN_HEIGHT - wall[i].h;
                                        }
                                        else if (i == 5)
                                        {
                                            if (wall[i].y >= 60)
                                                wall[i].y -= 50;
                                            else
                                                wall[i].y = 350;
                                        }
                                        int j = wall[i].h - wall[i + 1].h;
                                        if (j < 0)
                                            j = -j;
                                        if (j <= 70)
                                        {
                                            if (i == 2)
                                            {
                                                wall[i].h = 130;
                                                wall[i].y = SCREEN_HEIGHT - wall[i].h;
                                            }
                                            else if (i != 5)
                                            {
                                                wall[i].h = 130;
                                            }
                                        }
                                        else if (j > 100)
                                        {
                                            if (i == 2 || i == 1)
                                            {
                                                wall[i].h = 130;
                                                wall[i].y = SCREEN_HEIGHT - wall[i].h;
                                            }
                                            else if (i != 3 && i != 5)
                                            {
                                                wall[i].h = 130;
                                            }
                                        }
                                        changecolori[i] += 60;
                                        changecolorj[i] += 80;
                                        changecolork[i] += 50;
                                        if (changecolori[i] >= 400)
                                        {
                                            changecolori[i] = 0;
                                            changecolorj[i] = 0;
                                            changecolork[i] = 0;
                                        }
                                    }

                                }
                                SDL_SetRenderDrawColor(gRenderer, 190 + changecolori[0], 107 + changecolorj[0], 191 + changecolork[0], 255);

                                gBGTexture.render(scrollingOffset, 0);
                                gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);
                                dot.render();

                                for(int m = 0 ; m < 5 ;m++)
                                {
                                    gPillarTexture.render(wall[m].x, wall[m].y);
                                }
                                /*SDL_RenderDrawRect(gRenderer, &wall[0]);
                                SDL_RenderFillRect(gRenderer, &wall[0]);

                                SDL_SetRenderDrawColor(gRenderer, 90 + changecolori[1], 17 + changecolorj[1], 91 + changecolork[1], 255);
                                SDL_RenderDrawRect(gRenderer, &wall[1]);
                                SDL_RenderFillRect(gRenderer, &wall[1]);

                                SDL_SetRenderDrawColor(gRenderer, 10 + changecolori[2], 10 + changecolorj[2], 19 + changecolork[2], 255);
                                SDL_RenderDrawRect(gRenderer, &wall[2]);
                                SDL_RenderFillRect(gRenderer, &wall[2]);

                                SDL_SetRenderDrawColor(gRenderer, 40 + changecolori[3], 57 + changecolorj[3], 40 + changecolork[2], 255);
                                SDL_RenderDrawRect(gRenderer, &wall[3]);
                                SDL_RenderFillRect(gRenderer, &wall[3]);

                                SDL_SetRenderDrawColor(gRenderer, 90 + changecolori[4], 10 + changecolorj[4], 19 + changecolork[4], 255);
                                SDL_RenderDrawRect(gRenderer, &wall[4]);
                                SDL_RenderFillRect(gRenderer, &wall[4]);

                                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(gRenderer, &wall[5]);
                                SDL_RenderFillRect(gRenderer, &wall[5]);*/

                                //Render textures
                                gTimeTextTexture.render(180, (SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 20);

                                SDL_Rect *currentClip = &gSpriteClips[0];
                                gSpriteSheetTexture.render(loveWidth, 60 + loveHeight, currentClip);

                                SDL_Rect *idontknowClip = &gfoodyClips[0];
                                gfoodySheetTexture.render(foodWidth, foodHeight, idontknowClip);

                                SDL_RenderPresent(gRenderer);

                                for (int k = 1; k < scrollspeed; k++)
                                {
                                    score++;
                                    timeText.str("");
                                    timeText << "Score:" << score;
                                    timeText << "   Life:" << life;
                                }
                                if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
                                {
                                    printf("Unable to render time texture!\n");
                                }

                                love[0].x = loveWidth;
                                love[0].y = loveHeight + 60;
                                love[0].w = gSpriteClips[0].w;
                                love[0].h = gSpriteClips[0].h;

                                food[0].x = foodWidth;
                                food[0].y = foodHeight;
                                food[0].w = gfoodyClips[0].w;
                                food[0].h = gfoodyClips[0].h;

                                scrollspeed += 0.005;
                            }

                }
				if (x == 2)
				{
					x = loadinstructions();
				}

				if (x == 3)
				{
					x = loadhighscore();
				}
			}
		}

		//Free resources and close SDL
		close();

		return 0;
	}
}
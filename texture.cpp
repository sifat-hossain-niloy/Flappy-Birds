#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>

#include "texture.h"
using namespace std;

int loadmenu()
{
	bool success = true;
	if (!gMenuTexture.loadFromFile("MENU.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gMenu1Texture.loadFromFile("1.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gMenu2Texture.loadFromFile("2.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gMenu3Texture.loadFromFile("3.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gMenu4Texture.loadFromFile("4.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	bool menuRun = true;

	while (menuRun)
	{
		gMenuTexture.render(0, 0);
		SDL_Event e;
		int x, y;
		SDL_GetMouseState(&x, &y);
		cout << x << " " << y << endl;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			if (x > 200 && x < 512)
			{
				if(y>285 && y < 360)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN )
					{
						kol=1;
						Mix_PlayMusic(gMusic,1);
						return 1;
					}
					else
					{
						gMenu1Texture.render(0, 0);
					}
				}
				else if(y>385 && y < 460)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 2;
					}
					else
					{
						gMenu2Texture.render(0, 0);
					}
					
				}
				else if(y>500 && y < 580)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 3;
					}
					else
					{
						gMenu3Texture.render(0, 0);
					}
					
				}
				else if(y>615 && y < 685)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 0;
					}
					else
					{
						gMenu4Texture.render(0, 0);
					}
					
				}
			}

			if (e.type == SDL_KEYDOWN)
			{
				menuRun = false;
			}
		}
		SDL_RenderPresent(gRenderer);
	}

	return -1;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Courier.ttf", 34);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color
		SDL_Color textColor = {176, 48, 96, 255};

		//Load prompt texture
		if (!gPromptTextTexture.loadFromRenderedText(" ", textColor))
		{
			printf("Unable to render prompt texture!\n");
			success = false;
		}
	}

	//Load background texture
	if (!gBGTexture.loadFromFile("dreamy night.jpg"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!gPillarTexture.loadFromFile("Pillar1.png"))
	{
		printf("Failed to load pillar texture!\n");
		success = false;
	}
	//Load dot texture
	if (!gDotTexture.loadFromFile("birdy.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("love2.png"))
	{
		printf("Failed to load love texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips

		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 20;
		gSpriteClips[0].h = 20;
	}

	if (!gfoodySheetTexture.loadFromFile("kkk.bmp"))
	{
		printf("Failed to load food texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips

		gfoodyClips[0].x = 0;
		gfoodyClips[0].y = 0;
		gfoodyClips[0].w = 35;
		gfoodyClips[0].h = 35;
	}

	gScratch = Mix_LoadWAV("newitm2.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

    gMusic = Mix_LoadMUS("melodyloops-preview-children-train-15m30s.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

int loadhighscore()
{

	SDL_Surface *image = SDL_LoadBMP("t.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, image);
	
	FILE *fPtr;
	long long int a[3];
	char p[10000];
	int i = 0;
	fPtr = fopen("highscore.txt", "r");

	while (fscanf(fPtr, "%lld", &a[i]) == 1)
	{
		i++;
		if (i == 3)
			break;
	}
	fclose(fPtr);

	sprintf(p,"%lld  %lld  %lld",a[0],a[1],a[2]);
	int ll=strlen(p);
	p[ll-1]='\0';

	SDL_Color textColor = {0, 48, 96, 255};

	while (1)
	{
		SDL_RenderCopy(gRenderer, texture, NULL, NULL);
		SDL_Event e;
		int x, y;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			
			if (e.type == SDL_KEYDOWN)
			{
				//Adjust the velocity
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					return -1;
				}
			}
		}
		for(int m = 0 ; m < 3 ; m++)
		{
		timeText.str(" ");

		timeText << "" << a[m];
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			printf("Unable to render time texture!\n");
		}
		gTimeTextTexture.render(300, ((SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 2.9)+30+(m*100));

		}
		SDL_RenderPresent(gRenderer);
		SDL_Delay(15);
	}
	    
	return 3;
}

int loadinstructions(){
    SDL_Surface *image = SDL_LoadBMP("Ins.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, image);
	
	
	while (1)
	{
		SDL_RenderCopy(gRenderer, texture, NULL, NULL);
		SDL_Event e;
		int x, y;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			
			if (e.type == SDL_KEYDOWN)
			{
				//Adjust the velocity
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					return -1;
				}
			}
		}
		SDL_RenderPresent(gRenderer);
		SDL_Delay(15);
	}


	return 2;
}
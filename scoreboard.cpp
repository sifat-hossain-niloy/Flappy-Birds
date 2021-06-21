#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

#include "defs.h"

#include <bits/stdc++.h>

using namespace std;

void loadscoreboard()
{
	SDL_Delay(1000);
	SDL_Surface *image = SDL_LoadBMP("now.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, image);
	SDL_RenderCopy(gRenderer, texture, NULL, NULL);
	/* File pointer to hold reference to our file */
	FILE *fPtr;
	long long int a[3], temp;
	char p[10000];
	int i = 0;
	fPtr = fopen("highscore.txt", "r");

	while (fscanf(fPtr, "%lld", &a[i]) == 1)
	{
		i++;
		if (i == 3)
			break;
	}
	if (score >= a[0])
	{
		a[1] = a[0];
		a[2] = a[1];
		a[0] = score;
	}
	else if (score >= a[1])
	{
		a[2] = a[1];
		a[1] = score;
	}
	else if (score >= a[2])
	{
		a[2] = score;
	}

	FILE *fPtw = fopen("highscore.txt", "w");
	fprintf(fPtw, "%lld\n%lld\n%lld\n", a[0], a[1], a[2]);


	fclose(fPtw);
	fclose(fPtr);

	int gotIt = 0;

	SDL_Color textColor = {255, 255, 255, 255};

	for(int m = 0 ; m < 3 ; m++)
	{
		if (score >= a[i])
		{
			timeText.str(" ");
			gotIt =1;

			timeText << "Your Position:" << i+1;
			if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
			{
				printf("Unable to render time texture!\n");
			}
			if (!gPromptTextTexture.loadFromRenderedText("Congratulations!!!", textColor))
			{
				printf("Unable to render prompt texture!\n");
			}
			gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 6, 350);
			gTimeTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 6, 420);
		}
	}

	SDL_RenderPresent(gRenderer);
	SDL_Delay(3000);
	return;
}
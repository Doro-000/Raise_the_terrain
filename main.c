#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define GRID_SPACING 95
#define GRID_SIZE 7

float *ToIso(float *point);

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	SDL_Window *my_window = NULL;
	SDL_Renderer *my_renderer = NULL;
	SDL_Event event;
	int EXIT = 0;
	int i, j;
	float origin[2];
	float dest[2];
	float *iso_initial;
	float *iso_dest;
 	// j, k, z;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
	else
	{
		my_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (my_window == NULL)
			fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		else
		{
			my_renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED);
			while (!EXIT)
			{
				//clear screen
				SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(my_renderer);

				origin[0] = 550.0;
				origin[1] = -150.0;
				SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
				//Draw Horizontal lines
				for (i = 0; i < GRID_SIZE + 1; i++)
				{
					for (j = 0; j < GRID_SIZE; j++)
					{
						dest[0] = origin[0] + GRID_SPACING;
						dest[1] = origin[1];
						iso_initial = ToIso(origin);
						iso_dest = ToIso(dest);
						SDL_RenderDrawLine(my_renderer, iso_initial[0], iso_initial[1], iso_dest[0], iso_dest[1]);
						origin[0] += GRID_SPACING;
						free(iso_initial);
						free(iso_dest);
					}
					origin[0] = 550.0; // reset x;
					origin[1] += GRID_SPACING;
				}
				//reset Y
				origin[1] = -150.0;
				//draw vertical lines
				for (i = 0; i < GRID_SIZE + 1; i++)
				{
					for (j = 0; j < GRID_SIZE; j++)
					{
						dest[0] = origin[0];
						dest[1] = origin[1] + GRID_SPACING;
						iso_initial = ToIso(origin);
						iso_dest = ToIso(dest);
						SDL_RenderDrawLine(my_renderer, iso_initial[0], iso_initial[1], iso_dest[0], iso_dest[1]);
						origin[1] += GRID_SPACING;
						free(iso_initial);
						free(iso_dest);
					}
					origin[1] = -150.0; //reset y;
					origin[0] += GRID_SPACING;
				}
				//reset x
				origin[0] = 550.0;

				SDL_RenderPresent(my_renderer);
				// SDL_Delay(20);
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						EXIT = 1;
				}
			}
		}
	}
	SDL_DestroyWindow(my_window);
	SDL_DestroyRenderer(my_renderer);
	SDL_Quit();
	return (0);
}


float *ToIso(float *point)
{
	float *new_point;
	new_point = malloc(sizeof(new_point) * 2);
	new_point[0] = (point[0] * 0.7) - (point[1] *0.7);
	new_point[1] = ((1 - 0.7) * point[0]) + ((1 - 0.7) * point[1]) - 0;
	return (new_point);
}
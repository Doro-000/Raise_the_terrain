#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	SDL_Window *my_window = NULL;
	SDL_Surface *my_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
	else
	{
		my_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (my_window == NULL)
			fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		else
		{
			my_surface = SDL_GetWindowSurface(my_window);
			SDL_FillRect(my_surface, NULL, SDL_MapRGB(my_surface->format, 0xFF, 0xFF, 0x00));
			SDL_UpdateWindowSurface(my_window);
			SDL_Delay(2000);
		}
	}
	SDL_DestroyWindow(my_window);
	SDL_Quit();
	return (0);
}

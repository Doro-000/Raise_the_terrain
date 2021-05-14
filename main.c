#include "iso.h"


/**
 * main - entry point
 * @argc: number of args passed to the program
 * @argv: list of arguments
 *
 * Return: 0 on success, or exit with EXIT_FAILURE on errors
 */
int main(int argc, char *argv[])
{
	SDL_Window *my_window = NULL;
	SDL_Renderer *my_renderer = NULL;
	SDL_Event event;
	int EXIT = 0;
	float origin[2] = {750.0, -150.0};
	int **altitude = NULL;
	float ***grid = NULL;
	FILE *altitude_file = NULL;
	
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: ./terrain <file>\n");
		exit(EXIT_FAILURE);
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) /*Initialize SDL*/
	{
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	my_window = SDL_CreateWindow("Isometric Grid", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, 0); /*Create window*/
	if (my_window == NULL)
	{
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	my_renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED);
	altitude_file = fopen(argv[1], "r");
	grid = get_grid(origin); /*setup grid*/
	altitude = get_altitude(altitude_file);
	fclose(altitude_file);
	ToIso(grid, altitude);	
	while (!EXIT)
	{
		SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(my_renderer); /*clear screen*/
		SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		draw_horizontal(grid, my_renderer);
		draw_vertical(grid, my_renderer);
		SDL_RenderPresent(my_renderer);
		SDL_Delay(200);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				EXIT = 1;
		}
	}
	free_3D(grid);
	free_2D(altitude);
	SDL_DestroyWindow(my_window);
	SDL_DestroyRenderer(my_renderer);
	SDL_Quit();
	return (0);
}

#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define GRID_SPACING 120
#define GRID_SIZE 7
#define INC 0.55

void ToIso(float ***, int **);
float ***get_grid(float *);



int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	SDL_Window *my_window = NULL;
	SDL_Renderer *my_renderer = NULL;
	SDL_Event event;
	int EXIT = 0;
	int i, j;
	float origin[2] = {750.0, -150.0};
	int **altitude = NULL;
	float ***grid = NULL;
	float initial[2] = {0, 0};
	float dest[2] = {0, 0};


	altitude = malloc(sizeof(*altitude) * (GRID_SIZE + 1));
	for(i=0; i <= GRID_SIZE; i++) 
	{
		altitude[i]= malloc(sizeof(**altitude) * (GRID_SIZE + 1));
	}
	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j <= GRID_SIZE; j++)
		{
			altitude[i][j] = 0;
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
	else
	{
		my_window = SDL_CreateWindow("Isometric Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (my_window == NULL)
			fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		else
		{
			my_renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED);

			grid = get_grid(origin);
			ToIso(grid, altitude);			
			while (!EXIT)
			{
				//clear screen
				SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(my_renderer);

				SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

				for(i = 0; i <= GRID_SIZE; i++) 
				{
					for(j = 0; j < GRID_SIZE; j++) 
					{
						initial[0] = grid[i][j][0];
						initial[1] = grid[i][j][1];
						dest[0] = grid[i][j + 1][0];
						dest[1] = grid[i][j + 1][1];
						SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
						// SDL_RenderDrawPoint(my_renderer, grid[i][j][0], grid[i][j][1]);
					}
				}

				for(i = 0; i <= GRID_SIZE; i++) 
				{
					for(j = 0; j < GRID_SIZE; j++) 
					{
						initial[0] = grid[j][i][0];
						initial[1] = grid[j][i][1];
						dest[0] = grid[j + 1][i][0];
						dest[1] = grid[j + 1][i][1];
						SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
						// SDL_RenderDrawPoint(my_renderer, grid[i][j][0], grid[i][j][1]);
					}
				}
	
				SDL_RenderPresent(my_renderer);
				SDL_Delay(20);
				// free(grid);
				// origin[0] += 1;
				// // origin[1] += 1;
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						EXIT = 1;
				}
			}
		}
	}
	free(grid);
	SDL_DestroyWindow(my_window);
	SDL_DestroyRenderer(my_renderer);
	SDL_Quit();
	return (0);
}


void ToIso(float ***my_grid, int **altitude)
{
	float *temp_point;
	int Z, i, j;

	for(i = 0; i <= GRID_SIZE; i++) 
	{
		for(j = 0; j <= GRID_SIZE; j++) 
		{
			temp_point = my_grid[i][j];
			my_grid[i][j][0] = (temp_point[0] * INC) - (temp_point[1] * INC);
			Z = altitude[i][j];
			my_grid[i][j][1] = ((1 - INC) * temp_point[0]) + ((1 - INC) * temp_point[1]) - Z;
		}
	}
}

float ***get_grid(float *origin)
{
	int i, j;
	float ***my_grid = NULL;

	my_grid = malloc(sizeof(*my_grid) * (GRID_SIZE + 1));
	for(i=0; i <= GRID_SIZE; i++) 
	{
		my_grid[i]= malloc(sizeof(**my_grid) * (GRID_SIZE + 1));
		for(j=0; j <= GRID_SIZE; j++) 
			my_grid[i][j]= malloc(sizeof(***my_grid) * 2);
	}

	for(i = 0; i <= GRID_SIZE; i++) 
	{
		for(j = 0; j <= GRID_SIZE; j++) 
		{
			my_grid[i][j][0] = origin[0] + (j * GRID_SPACING);
			my_grid[i][j][1] = origin[1] + (i * GRID_SPACING);
		}
	}
	return (my_grid);
}

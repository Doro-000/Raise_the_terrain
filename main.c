#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define GRID_SPACING 120
#define GRID_SIZE 7
#define INC 0.55

void draw_vertical(float ***grid, SDL_Renderer *my_renderer);
void draw_horizontal(float ***grid, SDL_Renderer *my_renderer);
int **get_altitude(FILE *altitude_file);
float ***get_grid(float *origin);
void ToIso(float ***my_grid, int **altitude);
void free_3D(float ***cube);
void free_2D(int **table);

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

void free_2D(int **table)
{
	int i;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		free(table[i]);
	}
	free(table);
}

void free_3D(float ***cube)
{
	int i, j;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j <= GRID_SIZE; j++)
		{
			free(cube[i][j]);
		}
		free(cube[i]);
	}
	free(cube);
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

int **get_altitude(FILE *altitude_file)
{
	int **grid = NULL;
	int i, j;
	char line[256];
	char *token = NULL;

	grid = malloc(sizeof(*grid) * (GRID_SIZE + 1));
	for (i = 0; i <= GRID_SIZE; i++)
	{
		grid[i] = malloc(sizeof(**grid) * (GRID_SIZE + 1));
	}
	
	i = 0;
	while (fgets(line, sizeof(line), altitude_file))
	{
		j = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			grid[i][j] = atoi(token);
			token = strtok(NULL, " ");
			j++;
		}
		i++;
	}
	return (grid);
}

void draw_horizontal(float ***grid, SDL_Renderer *my_renderer)
{
	float initial[2] = {0, 0};
	float dest[2] = {0, 0};
	int i, j;

	for(i = 0; i <= GRID_SIZE; i++) 
	{
		for(j = 0; j < GRID_SIZE; j++) 
		{
			initial[0] = grid[i][j][0];
			initial[1] = grid[i][j][1];
			dest[0] = grid[i][j + 1][0];
			dest[1] = grid[i][j + 1][1];
			SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
		}
	}
}

void draw_vertical(float ***grid, SDL_Renderer *my_renderer)
{
	float initial[2] = {0, 0};
	float dest[2] = {0, 0};
	int i, j;

	for(i = 0; i <= GRID_SIZE; i++) 
	{
		for(j = 0; j < GRID_SIZE; j++) 
		{
			initial[0] = grid[j][i][0];
			initial[1] = grid[j][i][1];
			dest[0] = grid[j + 1][i][0];
			dest[1] = grid[j + 1][i][1];
			SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
		}
	}
}
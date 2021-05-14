#include "iso.h"

/**
 * draw_horizontal - draws horizontal lines from a grid
 * @grid: grid to be used
 * @my_renderer: renderer to draw the lines
 *
 * Reuturn: void
 */
void draw_horizontal(float ***grid, SDL_Renderer *my_renderer)
{
	float initial[2] = {0, 0};
	float dest[2] = {0, 0};
	int i, j;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			initial[0] = grid[i][j][0];
			initial[1] = grid[i][j][1];
			dest[0] = grid[i][j + 1][0];
			dest[1] = grid[i][j + 1][1];
			SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
		}
	}
}

/**
 * draw_vertical - draws vertical lines given a grid
 * @grid: grid to be used
 * @my_renderer: renderer to draw the lines
 *
 * Return: void
 */
void draw_vertical(float ***grid, SDL_Renderer *my_renderer)
{
	float initial[2] = {0, 0};
	float dest[2] = {0, 0};
	int i, j;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			initial[0] = grid[j][i][0];
			initial[1] = grid[j][i][1];
			dest[0] = grid[j + 1][i][0];
			dest[1] = grid[j + 1][i][1];
			SDL_RenderDrawLine(my_renderer, initial[0], initial[1], dest[0], dest[1]);
		}
	}
}

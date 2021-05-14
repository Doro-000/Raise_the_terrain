#include "iso.h"

/**
 * free_2D - frees a 2d array
 * @table: array to be freed
 *
 * Return: void
 */
void free_2D(int **table)
{
	int i;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		free(table[i]);
	}
	free(table);
}

/**
 * free_3D - frees a 3d array
 * @cube: array to be freed
 *
 * Return: void
 */
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

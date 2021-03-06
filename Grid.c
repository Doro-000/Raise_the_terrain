#include "iso.h"


/**
 * ToIso - converts the 3d points given in a grid to 2d
 * @my_grid: gird to be used
 * @altitude: Z coordinates to be used
 *
 * Return: void
 */
void ToIso(float ***my_grid, int **altitude)
{
	float *temp;
	int Z, i, j;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j <= GRID_SIZE; j++)
		{
			temp = my_grid[i][j];
			my_grid[i][j][0] = (temp[0] * INC) - (temp[1] * INC);
			Z = altitude[i][j];
			my_grid[i][j][1] = ((1 - INC) * temp[0]) + ((1 - INC) * temp[1]) - Z;
		}
	}
}

/**
 * get_grid - generates a set of points given an initial point
 * @origin: initial point
 *
 * Return: a 3d array containing the generated points
 */
float ***get_grid(float *origin)
{
	int i, j;
	float ***my_grid = NULL;

	my_grid = malloc(sizeof(*my_grid) * (GRID_SIZE + 1));
	for (i = 0; i <= GRID_SIZE; i++)
	{
		my_grid[i] = malloc(sizeof(**my_grid) * (GRID_SIZE + 1));
		for (j = 0; j <= GRID_SIZE; j++)
			my_grid[i][j] = malloc(sizeof(***my_grid) * 2);
	}

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j <= GRID_SIZE; j++)
		{
			my_grid[i][j][0] = origin[0] + (j * GRID_SPACING);
			my_grid[i][j][1] = origin[1] + (i * GRID_SPACING);
		}
	}
	return (my_grid);
}

/**
 * get_altitude - scans a file to Z coordinates
 * @altitude_file: file stream to be used
 *
 * Return: a 2d array containing the read coordinates
 */
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
	fclose(altitude_file);
	return (grid);
}

/**
 * apply_rotation - applies rotation to given points
 * @my_grid: gird to be used
 * @angle: angle to be used
 *
 * Return: void
 */
void apply_rotation(float ***my_grid, double angle)
{
	float *temp;
	double radians;
	int i, j;

	for (i = 0; i <= GRID_SIZE; i++)
	{
		for (j = 0; j <= GRID_SIZE; j++)
		{
			temp = my_grid[i][j];
			radians = (angle * M_PI) / 180;
			my_grid[i][j][0] = temp[0] * cos(radians) - temp[1] * sin(radians);
			my_grid[i][j][1] = temp[0] * sin(radians) + temp[1] * cos(radians);
		}
	}
}

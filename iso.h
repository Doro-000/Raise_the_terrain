#ifndef ISO_H
#define ISO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>

/*Constants*/
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define GRID_SPACING 120
#define GRID_SIZE 7
#define INC 0.55

/*main*/
SDL_Window *sdl_init();
/*Draw*/
void draw_vertical(float ***grid, SDL_Renderer *my_renderer);
void draw_horizontal(float ***grid, SDL_Renderer *my_renderer);
/*Grid*/
int **get_altitude(FILE *altitude_file);
float ***get_grid(float *origin);
void ToIso(float ***my_grid, int **altitude);
void apply_rotation(float ***my_grid, double angle);
/*Free*/
void free_3D(float ***cube);
void free_2D(int **table);

#endif /*ISO_H*/

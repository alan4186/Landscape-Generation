/*

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "globals.h"
#include "types.h"
#include "tsp.h"

/* Prototypes */
short **tsp_init_grid_init(int x, int y);
void tsp_free_grid(int x, short ***grid);
float cartesian_distance(int x1, int y1, int x2, int y2);

/* globals */
//tsp_problem_t *tsp_problem;

/*---------------------------------------------------------------------------------------------
 * (function: tsp_free_problem)
 *-------------------------------------------------------------------------------------------*/
void tsp_free_problem() {
	int i;
	for (i = 0; i < tsp_problem->num_cities; i++) {
		free(tsp_problem->cities[i]);
	}

	free(tsp_problem->cities);
	free(tsp_problem);
}

/*---------------------------------------------------------------------------------------------
 * (function: tsp_init_problem)
 *-------------------------------------------------------------------------------------------*/
void tsp_init_problem(int num_cities) {
	short **grid;
	int i;
	int grid_size = (int) (sqrt(num_cities) * 3);

	printf("Initializing a specific problem, grid size: %d\n",grid_size);

	/* initialize the basic problem */
	tsp_problem = (tsp_problem_t*) malloc(sizeof(tsp_problem_t));

	/* initalize the grid that makes sure we don't have two cities in one spot */
	grid = tsp_init_grid_init(grid_size, grid_size);

	/* up to 32767 cities */
	tsp_problem->num_cities = num_cities;
	tsp_problem->cities = (tsp_city_t**) malloc(
			sizeof(tsp_city_t*) * tsp_problem->num_cities);

	// allocate memory for the corner permutations

	tsp_problem->u=(element_t**)malloc(num_cities*sizeof(element_t*));
	tsp_problem->d=(element_t**)malloc(num_cities*sizeof(element_t*));
	tsp_problem->l=(element_t**)malloc(num_cities*sizeof(element_t*));
	tsp_problem->r=(element_t**)malloc(num_cities*sizeof(element_t*));


	for (i = 0; i < tsp_problem->num_cities; i++) {
		tsp_problem->u[i]=(element_t*)malloc(sizeof(element_t));
		tsp_problem->d[i]=(element_t*)malloc(sizeof(element_t));
		tsp_problem->l[i]=(element_t*)malloc(sizeof(element_t));
		tsp_problem->r[i]=(element_t*)malloc(sizeof(element_t));

		tsp_problem->cities[i] = (tsp_city_t*) malloc(sizeof(tsp_city_t));
		tsp_problem->cities[i]->id = i;
		tsp_problem->cities[i]->x = rand() % grid_size;
		tsp_problem->cities[i]->y = rand() % grid_size;

		/* check if there's a city already there*/
		while (grid[tsp_problem->cities[i]->x][tsp_problem->cities[i]->y] != 0) {
			tsp_problem->cities[i]->x = rand() % grid_size;
			tsp_problem->cities[i]->y = rand() % grid_size;
		}

		grid[tsp_problem->cities[i]->x][tsp_problem->cities[i]->y] = 1;
	}

	/* free initialization memory */
	tsp_free_grid(grid_size, &grid);
}

/*---------------------------------------------------------------------------------------------
 * (function: tsp_init_grid_init)
 *-------------------------------------------------------------------------------------------*/
short **tsp_init_grid_init(int x, int y) {
	int i, j;
	short **grid;

	grid = (short **) malloc(sizeof(short*) * x);

	for (i = 0; i < x; i++) {
		grid[i] = (short *) malloc(sizeof(short) * y);
		for (j = 0; j < y; j++) {
			grid[i][j] = 0;
		}
	}

	return grid;
}

/*---------------------------------------------------------------------------------------------
 * (function: tsp_free_grid)
 *-------------------------------------------------------------------------------------------*/
void tsp_free_grid(int x, short ***grid) {
	int i;

	for (i = 0; i < x; i++) {
		free(grid[0][i]);
	}
	free(grid[0]);
}

/*---------------------------------------------------------------------------------------------
 * (function: tsp_cost_function)
 *-------------------------------------------------------------------------------------------*/
float tsp_cost_function(element_t** solution) {
	int i;
	float cost = 0.0;

	for (i = 1; i < tsp_problem->num_cities; i++) {
			cost += cartesian_distance(
					tsp_problem->cities[solution[i]->id]->x,
					tsp_problem->cities[solution[i]->id]->y,
					tsp_problem->cities[solution[i - 1]->id]->x,
					tsp_problem->cities[solution[i - 1]->id]->y);
		}
	return cost;
}

/*---------------------------------------------------------------------------------------------
 * (function: cartesian_distance)
 *-------------------------------------------------------------------------------------------*/
inline float cartesian_distance(int x1, int y1, int x2, int y2) {
	/* calculate distance */
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}



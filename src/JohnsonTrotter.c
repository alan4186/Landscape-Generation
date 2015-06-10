/*
 * JohnsonTrotter.c
 *
 *  Created on: Apr 8, 2015
 *      Author: alan
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "globals.h"
#include "types.h"
//#include "tsp.h"
//#import "tsp.c"

/* prototypes */
void JohnsonTrotter(int n, const char * c,int *d);
void changeDir(int n);
int findMobile(int cityIndex);
void savePermutation();
void printPermutation();
float fast_tsp_cost_function(int mobile, float old_score);
float cartesian_distance(int x1, int y1, int x2, int y2);

/* globals */
int* npr; // create array of pointers to cities

void JohnsonTrotter(int n, const char * c,int * d) {
	tsp_init_problem(n,d);

	// initilaize array of pointers to cities
	npr = (int*) malloc(sizeof(int) * tsp_problem->num_cities);

	for(int i=0;i<tsp_problem->num_cities;i++){
		npr[i]=i;
	}

	//set index of nth city for swapMpbile
	int cityN = tsp_problem->num_cities - 1;
	// set index of mobile city
	int mobile = tsp_problem->num_cities - 1;
	// init score and score first permutation
	float score = tsp_cost_function(npr);

	// init file
	FILE *f;
	f= fopen(c, "w");

	//save map
	//fprintf(f,"Xmap = [");
	for (int i = 0; i < n; i++) {
		fprintf(f,"%d ", tsp_problem->cities[i]->x);
	}
	//fprintf(f,"]\nYmap = [");
	fprintf(f,"\n");

	for (int i = 0; i < n; i++) {
		fprintf(f,"%d ", tsp_problem->cities[i]->y);
	}
	fprintf(f,"\n");


	//while a mobile city exists
	while (mobile != -1) {
		//printPermutation();
		//savePermutation(f);
		fprintf(f,"%f\n", score);

		// score new chain
		score = fast_tsp_cost_function(mobile, score);

		//create tmp for mobile city
		int tmp = npr[mobile];

		// find nth city
		if(tsp_problem->cities[npr[mobile]]->id==n-1)
			cityN=mobile+tsp_problem->cities[npr[mobile]]->dir;
		else if(tsp_problem->cities[npr[mobile+tsp_problem->cities[npr[mobile]]->dir]]->id==n-1)
			cityN=mobile;

		//swap cities
		npr[mobile] = npr[tsp_problem->cities[tmp]->dir + mobile];
		npr[tsp_problem->cities[tmp]->dir + mobile] = tmp;

		// change direction of cities > mobileCity
		changeDir(tsp_problem->cities[tmp]->id);

		// find next mobile city
		mobile = findMobile(cityN);

	}
	//score = tsp_cost_function(npr);//score the last permutation
	//printPermutation();
	//savePermutation(f);
	fprintf(f,"%f\n", score);

	fclose(f);
	printf("end");
}

// search for the largest mobile city return its index
// check nth city first. it will be the nth city n/(n+1)% of the times
int findMobile(int cityIndex) {
	if (tsp_problem->cities[npr[cityIndex]]->dir + cityIndex > -1
			&& tsp_problem->cities[npr[cityIndex]]->dir + cityIndex < tsp_problem->num_cities
			&& tsp_problem->cities[npr[cityIndex]]->id > tsp_problem->cities[npr[tsp_problem->cities[npr[cityIndex]]->dir + cityIndex]]->id) {
		return cityIndex;
	}
	int m = -1;
	//check index 0
	if (tsp_problem->cities[npr[0]]->id > tsp_problem->cities[npr[1]]->id && tsp_problem->cities[npr[0]]->dir == 1) {
		m = 0;
	}

	for (int i = 1; i < tsp_problem->num_cities - 1; i++) {
		if (tsp_problem->cities[npr[i]]->id > tsp_problem->cities[npr[tsp_problem->cities[npr[i]]->dir + i]]->id
				&& (m == -1 || tsp_problem->cities[npr[i]]->id > tsp_problem->cities[npr[m]]->id)) {
			m = i;
		}
	}
	//check last index
	if (tsp_problem->cities[npr[tsp_problem->num_cities - 1]]->id
			> tsp_problem->cities[npr[tsp_problem->num_cities - 2]]->id
			&& tsp_problem->cities[npr[tsp_problem->num_cities - 1]]->dir == -1
			&& (m == -1 || tsp_problem->cities[npr[tsp_problem->num_cities - 1]]->id > tsp_problem->cities[npr[m]]->id)) {
		//printf("m was %d,",m);
		m = tsp_problem->num_cities - 1;
		//printf("m is %d.\n",m);
	}
	//printf("m is %d.\n",m);

	return m;
}

void changeDir(int n) {
	//check nth city
	if (n == tsp_problem->num_cities - 1) {
		return;
	}
	for (int i = tsp_problem->num_cities - 1; i > -1; i--) {
		if (tsp_problem->cities[i]->id > n) {
			tsp_problem->cities[i]->dir *= -1;
		} else {
			return;
		}
	}

}
void printPermutation() {
	for (int i = 0; i < tsp_problem->num_cities; i++) {
		int dir = tsp_problem->cities[npr[i]]->dir;
		if (dir == 1) {
			printf("%d> ", tsp_problem->cities[npr[i]]->id);
		} else if (tsp_problem->cities[npr[i]]->dir == -1) {
			printf("<%d ", tsp_problem->cities[npr[i]]->id);
		} else {
			printf("E%d,%d ",tsp_problem->cities[npr[i]]->id, tsp_problem->cities[npr[i]]->dir);
		}
	}
	printf("\n");
	//printf("%f\n",tsp_cost_function(npr));
}
void savePermutation(FILE *f) {
	/*
	for (int i = 0; i < tsp_problem->num_cities; i++) {

		int dir = tsp_problem->cities[npr[i]]->dir;
		if (dir == 1) {
			fprintf(f,"%d> ", tsp_problem->cities[npr[i]]->id);
		} else if (tsp_problem->cities[npr[i]]->dir == -1) {
			fprintf(f,"<%d ", tsp_problem->cities[npr[i]]->id);
		} else {
			fprintf(f,"E%d,%d ", tsp_problem->cities[npr[i]]->id, tsp_problem->cities[npr[i]]->dir);
		}
	}
	fprintf(f,"\t");
	//printf("%f\n",tsp_cost_function(npr));
 */
	for (int i=0;i<tsp_problem->num_cities; i++) {
		fprintf(f,"%d ", tsp_problem->cities[npr[i]]->id);
	}
}
/*---------------------------------------------------------------------------------------------
 * (function: fast_tsp_cost_function)
 *-------------------------------------------------------------------------------------------*/
float fast_tsp_cost_function(int mobile, float old_score) {
	float new_score = old_score;
	if (mobile == 0 || (mobile == 1 && tsp_problem->cities[npr[mobile]]->dir == -1)) {
		//[0 2]-[1 2]
		new_score +=
				(cartesian_distance(tsp_problem->cities[npr[0]]->x, tsp_problem->cities[npr[0]]->y, tsp_problem->cities[npr[2]]->x, tsp_problem->cities[npr[2]]->y)
						- cartesian_distance(tsp_problem->cities[npr[1]]->x, tsp_problem->cities[npr[1]]->y, tsp_problem->cities[npr[2]]->x,
								tsp_problem->cities[npr[2]]->y));
	} else if (mobile == tsp_problem->num_cities - 1
			|| (mobile == tsp_problem->num_cities - 2
					&& tsp_problem->cities[npr[tsp_problem->num_cities - 2]]->dir == 1)) {
		//[n n-2]-[n-1 n-2]
		new_score += (cartesian_distance(tsp_problem->cities[npr[tsp_problem->num_cities - 1]]->x,
				tsp_problem->cities[npr[tsp_problem->num_cities - 1]]->y,
				tsp_problem->cities[npr[tsp_problem->num_cities - 3]]->x,
				tsp_problem->cities[npr[tsp_problem->num_cities - 3]]->y)
				- cartesian_distance(tsp_problem->cities[npr[tsp_problem->num_cities - 2]]->x,
						tsp_problem->cities[npr[tsp_problem->num_cities - 2]]->y,
						tsp_problem->cities[npr[tsp_problem->num_cities - 3]]->x,
						tsp_problem->cities[npr[tsp_problem->num_cities - 3]]->y));
	} else {
		new_score += cartesian_distance(tsp_problem->cities[npr[mobile]]->x, tsp_problem->cities[npr[mobile]]->y,
				tsp_problem->cities[npr[(tsp_problem->cities[npr[mobile]]->dir * 2) + mobile]]->x,
				tsp_problem->cities[npr[(tsp_problem->cities[npr[mobile]]->dir * 2) + mobile]]->y);
		new_score += cartesian_distance(tsp_problem->cities[npr[mobile + tsp_problem->cities[npr[mobile]]->dir]]->x,
				tsp_problem->cities[npr[mobile + tsp_problem->cities[npr[mobile]]->dir]]->y,
				tsp_problem->cities[npr[mobile - tsp_problem->cities[npr[mobile]]->dir]]->x,
				tsp_problem->cities[npr[mobile - tsp_problem->cities[npr[mobile]]->dir]]->y);
		new_score -= cartesian_distance(tsp_problem->cities[npr[mobile]]->x, tsp_problem->cities[npr[mobile]]->y,
				tsp_problem->cities[npr[mobile - tsp_problem->cities[npr[mobile]]->dir]]->x,
				tsp_problem->cities[npr[mobile - tsp_problem->cities[npr[mobile]]->dir]]->y);
		new_score -= cartesian_distance(tsp_problem->cities[npr[tsp_problem->cities[npr[mobile]]->dir + mobile]]->x,
				tsp_problem->cities[npr[tsp_problem->cities[npr[mobile]]->dir + mobile]]->y,
				tsp_problem->cities[npr[(tsp_problem->cities[npr[mobile]]->dir * 2) + mobile]]->x,
				tsp_problem->cities[npr[(tsp_problem->cities[npr[mobile]]->dir * 2) + mobile]]->y);
	}
	return new_score;
}

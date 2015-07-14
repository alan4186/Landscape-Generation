/*
 * single_iteraion.c
 *
 * functions to compute single row of solutions in either dimensino
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
#include "tsp.h"

/* prototypes */
float* JTn(int n, int num2calc, element_t** perm);
void changeDir(int n,int max,element_t** perm);
int findMobile(int cityIndex,element_t** perm, int max);
//void savePermutation();
void printPermutation(element_t** perm);
float fast_tsp_cost_function(int mobile, float old_score,element_t** perm);
float tsp_var_cost_function(element_t** solution);

float cartesian_distance(int x1, int y1, int x2, int y2);
void backwards(int n,int num2calc,element_t** perm);
void forwards(int n,int num2calc,element_t** perm);

float* xdir(int num2calc){
	float* scores=(float*)malloc(sizeof(float)*num2calc);

	return scores;
}





/**
 *  n: the number of cities.
 * num2calc: the number of scores to calculate
 * perm: the permutation to start with
 *
 * if n<length(perm) end of perm should be constant
 */
/*
float* JTn(int n,int num2calc,element_t** perm) {

	// create array of scores to return
	float* scores=(float*)(malloc(sizeof(float)*num2calc));

	int cityN=-1;
	int cityNid=-1;
	//set index of nth city for swapMpbile
	for(int i=n-1;i>=0;i--){
		//if(perm[i]->id==n-1){
		if(perm[i]->id>cityNid && perm[i]->id<n ){
			cityN = i;
			cityNid=perm[i]->id;
			//break;
		}
	}
	// set index of mobile city
	int mobile = findMobile(cityN,perm,n);
	// init score and score first permutation
	scores[0] = tsp_cost_function(perm);

	// compute num2calc scores
	for(int i=1;i<num2calc;i++) {
		if (mobile==-1)
			for(int i=0;i<tsp_problem->num_cities;i++){
				perm[i]->id=i;
				perm[i]->dir=-1;
			}
		else{
		// print
		//printPermutation(perm);
		// score new chain
		scores[i] = fast_tsp_cost_function(mobile, scores[i-1],perm);

		//create tmp for mobile city
		element_t* tmp = perm[mobile];

		// find nth city
		if(perm[mobile]->id==n-1)
			cityN=mobile+perm[mobile]->dir;
		else if(perm[mobile+perm[mobile]->dir]->id==n-1)
			cityN=mobile;

		//swap cities
		perm[mobile] = perm[tmp->dir + mobile];
		perm[tmp->dir + mobile] = tmp;

		// change direction of cities > mobileCity
		changeDir(tmp->id,n,perm);

		// find next mobile city
		mobile = findMobile(cityN, perm,n);
		}
	}
	//printPermutation(perm);
	return scores;
}*/
float* JTn(int n,int num2calc,element_t** perm) {
	// create short permutation and swp vars
	element_t** originalPointer=perm;
	if(n<tsp_problem->num_cities){
		perm=(element_t**)malloc(n * sizeof(element_t*));
		int count=0;
		for(int i=0; i<tsp_problem->num_cities;i++){
			if(originalPointer[i]->id<n){
				perm[count]=originalPointer[i];
				count++;
			}
		}
	}
	// create array of scores to return
	float* scores=(float*)(malloc(sizeof(float)*num2calc));

	int cityN=-1;
	int cityNid=-1;
	//set index of nth city for swapMpbile
	for(int i=n-1;i>=0;i--){
		//if(perm[i]->id==n-1){
		if(perm[i]->id>cityNid && perm[i]->id<n ){
			cityN = i;
			cityNid=perm[i]->id;
			//break;
		}
	}
	//allocate tmp
	element_t* tmp = (element_t*)malloc(sizeof(element_t));
	// set index of mobile city
	int mobile = findMobile(cityN,perm,n);
	// init score and score first permutation
	scores[0] = tsp_var_cost_function(originalPointer);

	// compute num2calc scores
	for(int i=1;i<num2calc;i++) {
		if (mobile==-1)
			for(int i=0;i<n;i++){
				perm[i]->id=i;
				perm[i]->dir=-1;
			}
		else{
		// print
		//printPermutation(perm);

		//create tmp for mobile city
		memcpy(tmp,perm[mobile],sizeof(element_t));


		// find nth city
		if(perm[mobile]->id==n-1)
			cityN=mobile+perm[mobile]->dir;
		else if(perm[mobile+perm[mobile]->dir]->id==n-1)
			cityN=mobile;

		//swap cities
		memcpy(perm[mobile], perm[tmp->dir + mobile],sizeof(element_t));
		memcpy(perm[tmp->dir + mobile],tmp,sizeof(element_t));

		// change direction of cities > mobileCity
		changeDir(tmp->id,n,perm);

		// score new chain
		scores[i] = tsp_var_cost_function(originalPointer);

		// find next mobile city
		mobile = findMobile(cityN, perm,n);
		}
	}
	//printPermutation(perm);
	free(tmp);
	return scores;
}










// search for the largest mobile city return its index
// check nth city first. it will be the nth city n/(n+1)% of the times
int findMobile(int cityIndex, element_t** perm, int max) {
	if (perm[cityIndex]->dir + cityIndex > -1
			&& perm[cityIndex]->dir + cityIndex < max
			&& perm[cityIndex]->id > perm[perm[cityIndex]->dir + cityIndex]->id) {
		return cityIndex;
	}
	int m = -1;
	//check index 0
	if (perm[0]->id > perm[1]->id && perm[0]->dir == 1) {
		m = 0;
	}
	// checking middle indexes
	for (int i = 1; i < max - 1; i++) {
		if (perm[i]->id > perm[perm[i]->dir + i]->id
				&& (m == -1 || perm[i]->id > perm[m]->id)) {
			m = i;
		}
	}
	//check last index
	if (perm[max - 1]->id
			> perm[max - 2]->id
			&& perm[max - 1]->dir == -1
			&& (m == -1 || perm[max - 1]->id > perm[m]->id)) {
		m = max - 1;
	}
	return m;
}
/*
int findMobile(int cityIndex, element_t** perm, int max) {
	int m = -1;
	//check index 0
	if (perm[0]->id > perm[1]->id && perm[0]->dir == 1 ) {
		m = 0;
	}
	// checking middle indexes
	for (int i = 1; i < max - 1; i++) {
		if (perm[i]->id > perm[perm[i]->dir + i]->id
				&& (m == -1 || perm[i]->id > perm[m]->id)) {
			m = i;
		}
	}
	//check last index
	if (perm[max - 1]->id
			> perm[max - 2]->id
			&& perm[max - 1]->dir == -1
			&& (m == -1 || perm[max - 1]->id > perm[m]->id)) {
		m = max - 1;
	}
	return m;
}*/





/* n: the id of the city that just moved
 * max: the length of the permutation being generated
 * perm: the permutation
 */
void changeDir(int n,int max,element_t** perm) {
	//check nth city
	if (n == max - 1) {
		return;
	}
	for (int i = max - 1; i > -1; i--) {
		if (perm[i]->id > n && perm[i]->id<max) {
			perm[i]->dir *= -1;
		} //else {
			//return;
		//}
	}

}

void printPermutation(element_t** perm) {
	for (int i = 0; i < tsp_problem->num_cities; i++) {
		int dir = perm[i]->dir;
		if (dir == 1) {
			printf("%d> ",perm[i]->id);
		} else if (perm[i]->dir == -1) {
			printf("<%d ", perm[i]->id);
		} else {
			printf("E%d,%d ",perm[i]->id,perm[i]->dir);
		}
	}
	printf("\n");
}
/*
void savePermutation(FILE *f) {

	for (int i = 0; i < tsp_problem->num_cities; i++) {

		int dir = tsp_problem->cities[perm[i]]->dir;
		if (dir == 1) {
			fprintf(f,"%d> ", tsp_problem->cities[perm[i]]->id);
		} else if (tsp_problem->cities[perm[i]]->dir == -1) {
			fprintf(f,"<%d ", tsp_problem->cities[perm[i]]->id);
		} else {
			fprintf(f,"E%d,%d ", tsp_problem->cities[perm[i]]->id, tsp_problem->cities[perm[i]]->dir);
		}
	}
	fprintf(f,"\t");
	//printf("%f\n",tsp_cost_function(perm));

	for (int i=0;i<tsp_problem->num_cities; i++) {
		fprintf(f,"%d ", tsp_problem->cities[perm[i]]->id);
	}
}*/

/*---------------------------------------------------------------------------------------------
 * (function: fast_tsp_cost_function)
 *-------------------------------------------------------------------------------------------*/
float fast_tsp_cost_function(int mobile, float old_score, element_t** perm) {
	float new_score = old_score;
	if (mobile == 0 || (mobile == 1 && perm[mobile]->dir == -1)) {
		//[0 2]-[1 2]
		new_score +=
				(cartesian_distance(
						tsp_problem->cities[perm[0]->id]->x,
						tsp_problem->cities[perm[0]->id]->y,
						tsp_problem->cities[perm[2]->id]->x,
						tsp_problem->cities[perm[2]->id]->y)
			   - cartesian_distance(
					    tsp_problem->cities[perm[1]->id]->x,
					    tsp_problem->cities[perm[1]->id]->y,
						tsp_problem->cities[perm[2]->id]->x,
						tsp_problem->cities[perm[2]->id]->y));

	} else if (mobile == tsp_problem->num_cities - 1
			|| (mobile == tsp_problem->num_cities - 2
					&& perm[tsp_problem->num_cities - 2]->dir == 1)) {
		//[n n-2]-[n-1 n-2]
		new_score += (cartesian_distance(
				tsp_problem->cities[perm[tsp_problem->num_cities - 1]->id]->x,
				tsp_problem->cities[perm[tsp_problem->num_cities - 1]->id]->y,
				tsp_problem->cities[perm[tsp_problem->num_cities - 3]->id]->x,
				tsp_problem->cities[perm[tsp_problem->num_cities - 3]->id]->y)
				- cartesian_distance(
						tsp_problem->cities[perm[tsp_problem->num_cities - 2]->id]->x,
						tsp_problem->cities[perm[tsp_problem->num_cities - 2]->id]->y,
						tsp_problem->cities[perm[tsp_problem->num_cities - 3]->id]->x,
						tsp_problem->cities[perm[tsp_problem->num_cities - 3]->id]->y));
	} else {
		new_score += cartesian_distance(
				tsp_problem->cities[perm[mobile]->id]->x,
				tsp_problem->cities[perm[mobile]->id]->y,
				tsp_problem->cities[perm[(perm[mobile]->dir * 2) + mobile]->id]->x,
				tsp_problem->cities[perm[(perm[mobile]->dir * 2) + mobile]->id]->y);
		new_score += cartesian_distance(
				tsp_problem->cities[perm[mobile + perm[mobile]->dir]->id]->x,
				tsp_problem->cities[perm[mobile + perm[mobile]->dir]->id]->y,
				tsp_problem->cities[perm[mobile - perm[mobile]->dir]->id]->x,
				tsp_problem->cities[perm[mobile - perm[mobile]->dir]->id]->y);
		new_score -= cartesian_distance(
				tsp_problem->cities[perm[mobile]->id]->x,
				tsp_problem->cities[perm[mobile]->id]->y,
				tsp_problem->cities[perm[mobile - perm[mobile]->dir]->id]->x,
				tsp_problem->cities[perm[mobile - perm[mobile]->dir]->id]->y);
		new_score -= cartesian_distance(
				tsp_problem->cities[perm[perm[mobile]->dir + mobile]->id]->x,
				tsp_problem->cities[perm[perm[mobile]->dir + mobile]->id]->y,
				tsp_problem->cities[perm[(perm[mobile]->dir * 2) + mobile]->id]->x,
				tsp_problem->cities[perm[(perm[mobile]->dir * 2) + mobile]->id]->y);
	}
	return new_score;
}

float tsp_var_cost_function(element_t** solution) {
	int i;
	float cost = 0.0;
	for (i = 1; i < tsp_problem->num_cities; i++) {
			cost += cartesian_distance(tsp_problem->cities[solution[i]->id]->x,
					tsp_problem->cities[solution[i]->id]->y,
					tsp_problem->cities[solution[i - 1]->id]->x,
					tsp_problem->cities[solution[i - 1]->id]->y);
		}
	return cost;
}

void backwards(int n,int num2calc,element_t** perm) {
	// create short permutation and swp vars
	element_t** originalPointer=perm;
	if(n<tsp_problem->num_cities){
		perm=(element_t**)malloc(n * sizeof(element_t*));
		int count=0;
		for(int i=0; i<tsp_problem->num_cities;i++){
			if(originalPointer[i]->id<n){
				perm[count]=originalPointer[i];
				count++;
			}
		}
	}
	int cityN=-1;
	int cityNid=-1;
	//set index of nth city for swapMpbile
	for(int i=n-1;i>=0;i--){
		//if(perm[i]->id==n-1){
		if(perm[i]->id>cityNid){
			cityN = i;
			cityNid=perm[i]->id;
			//break;
		}
	}
	// reverse all directions
	for(int i=0;i<n;i++){
		perm[i]->dir=perm[i]->dir*-1;
	}
	//printf("reversed: ");
	//printPermutation(perm);
	// set index of mobile city
	int mobile;

	//allocate tmp
	element_t* tmp = (element_t*)malloc(sizeof(element_t));
	// compute num2calc scores
	for(int i=0;i<num2calc;i++) {
		// find next mobile city
		mobile = findMobile(cityN, perm,n);
		if (mobile==-1){
			/*
			element_t* tmp=perm[1];
			perm[1]=perm[0];
			perm[0]=tmp;
			for(int i=2;i<n;i++)
				perm[i]->dir*=-1;
			*/
			for(int i=2;i<n;i++){
				perm[i]->dir=-1;
				perm[i]->id=i;
			}
			perm[0]->id=1;
			perm[1]->id=0;
			perm[0]->dir=1;
			perm[1]->dir=1;
		}
		else{
		// print
		//printPermutation(perm);
		// score new chain
		//scores[i] = fast_tsp_cost_function(mobile, scores[i-1],perm);

		//create tmp for mobile city
		memcpy(tmp,perm[mobile],sizeof(element_t));

		// find nth city
		if(perm[mobile]->id==n-1)
			cityN=mobile+perm[mobile]->dir;
		else if(perm[mobile+perm[mobile]->dir]->id==n-1)
			cityN=mobile;

		//swap cities
		memcpy(perm[mobile], perm[tmp->dir + mobile],sizeof(element_t));
		memcpy(perm[tmp->dir + mobile],tmp,sizeof(element_t));

		// change direction of cities > mobileCity
		changeDir(tmp->id,n,perm);
		}


	}
	// reverse all directions again
	for(int i=0;i<n;i++){
		perm[i]->dir=perm[i]->dir*-1;
	}
	free(tmp);
	perm=originalPointer;
	//printPermutation(perm);
}

void forwards(int n,int num2calc,element_t** perm) {
	// create short permutation and swp vars
	element_t** originalPointer=perm;
	if(n<tsp_problem->num_cities){
		perm=(element_t**)malloc(n * sizeof(element_t*));
		int count=0;
		for(int i=0; i<tsp_problem->num_cities;i++){
			if(originalPointer[i]->id<n){
				perm[count]=originalPointer[i];
				count++;
			}
		}
	}
	int cityN=-1;
	int cityNid=-1;
	//set index of nth city for swapMpbile
	for(int i=n-1;i>=0;i--){
		//if(perm[i]->id==n-1){
		if(perm[i]->id>cityNid && perm[i]->id<n ){
			cityN = i;
			cityNid=perm[i]->id;
			//break;
		}
	}
	// set index of mobile city
	//allocate tmp
	element_t* tmp = (element_t*)malloc(sizeof(element_t));
	// compute num2calc scores
	for(int i=0;i<num2calc;i++) {
		int mobile = findMobile(cityN,perm,n);

		if (mobile==-1)
			for(int i=0;i<n;i++){
				perm[i]->id=i;
				perm[i]->dir=-1;
			}
		else{
		// print
		//printPermutation(perm);
		// score new chain

		//create tmp for mobile city
		memcpy(tmp,perm[mobile],sizeof(element_t));

		// find nth city
		if(perm[mobile]->id==n-1)
			cityN=mobile+perm[mobile]->dir;
		else if(perm[mobile+perm[mobile]->dir]->id==n-1)
			cityN=mobile;

		//swap cities
		memcpy(perm[mobile], perm[tmp->dir + mobile],sizeof(element_t));
		memcpy(perm[tmp->dir + mobile],tmp,sizeof(element_t));

		// change direction of cities > mobileCity
		changeDir(tmp->id,n,perm);

		// find next mobile city
		//mobile = findMobile(cityN, perm,n);
		}
	}
	free(tmp);
	perm=originalPointer;
	//printPermutation(perm);

}

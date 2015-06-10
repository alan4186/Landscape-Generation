#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"
#include "genetic_algorithm.h"
#include "tsp.h"

extern global_args_t global_args;
extern ga_pop_t genomes;
extern tsp_problem_t *tsp_problem;
extern float global_best;
extern FILE *fresult_out;

#endif


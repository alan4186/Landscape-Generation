
#ifndef TSP_H
#define TSP_H

typedef struct tsp_problem_t_t tsp_problem_t;
typedef struct tsp_city_t_t tsp_city_t;
typedef struct element_t_t element_t;

void tsp_free_problem();
void tsp_init_problem(int num_cities);
int *tsp_create_random_solution();
float tsp_cost_function(element_t** solution);

struct tsp_problem_t_t {
	int num_cities;
	int short_perm;
	tsp_city_t **cities;
	element_t ** u;
	element_t ** d;
	element_t ** l;
	element_t ** r;
};

struct tsp_city_t_t {
	int id;
	int x;
	int y;
};

struct element_t_t {
	short dir;
	int id;
};

#endif // TSP_H


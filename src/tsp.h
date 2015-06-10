void tsp_free_problem();
void tsp_init_problem(int num_cities,int * d);
int *tsp_create_random_solution();
float tsp_cost_function(int *solution);

#ifndef TSP_H
#define TSP_H

typedef struct tsp_problem_t_t tsp_problem_t;
typedef struct tsp_city_t_t tsp_city_t;


struct tsp_problem_t_t {
	int num_cities;
	tsp_city_t **cities;
};

struct tsp_city_t_t {
	short dir;
	int id;
	int x;
	int y;
};

#endif // TSP_H


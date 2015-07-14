void ga_init(population_t **(*fptr_init_starting_population)(int));
void ga_clean(void (*fptr_clean_population)(population_t **, int));
int run_base_ga(void (*fptr_cost_function_order)(population_t **, int),
		void (*fptr_copy_old_over)(population_t**, population_t**, int, int),
		void (*fptr_cross_breed)(population_t**, population_t**, int, int, int),
		void (*fptr_mutate)(population_t**, population_t**, int, int, int),
		void (*fptr_cross_and_mutate)(population_t**, population_t**, int, int,
				int), void (*fptr_random_new)(population_t**, int, int),
		short (*fptr_exit_condition)(void));


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

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TYPES_H
#define TYPES_H

typedef struct global_args_t_t global_args_t;

//#define oassert(x) {if(!(x)){exit(-1);}} // causes an interrupt in GDB
#define oassert(x) {if(!(x)){__asm("int3");}} // causes an interrupt in GDB
/* the global arguments of the software */
struct global_args_t_t {
	char *config_file;
	char *output_file;
};

typedef struct ga_pop_t_t ga_pop_t;
typedef struct population_t_t population_t;
typedef struct parent_history_t_t parent_history_t;

struct ga_pop_t_t {
	int num_population;
	population_t ***population;

	/* total for 4 params = 1 */
	float percent_to_keep;
	float percent_from_mutate;
	float percent_from_breed;
	float percent_from_breed_and_mutate;
	float percent_to_random;

	float top_percent_to_breed_from;
	float top_percent_to_mutate_from;
	float top_percent_to_breed_mutate_from;

	float percent_of_genome_mutations;

	int max_generations;
	int num_parents;
};

struct population_t_t {
	long long int id;
	void *genome;
	parent_history_t *parents;
};

struct parent_history_t_t {
	long long int *ids;
};

#endif // TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//#include <sys/time.h>
#include "tsp.h"
#include <gmp.h>

/* prototypes */
void tsp_init_problem(int num_cities);
float* JTn(int n, int num2calc, element_t** perm);
long int compute_space_dimensions(long int n, mpz_t num_rows,mpz_t num_col);
//size_t mpz_out_str (FILE *stream, int base, const mpz_t op);
void mpz_set (mpz_t rop, const mpz_t op);
size_t mpz_out_str (FILE *stream, int base, const mpz_t op);
void mpz_add_ui (mpz_t rop, const mpz_t op1, unsigned long int op2);
int init(int argc, char **argv,element_t** perm);
float** initSpace(int hdist,element_t** perm,int short_perm);
void backwards(int n,int num2calc,element_t** perm);
void forwards(int n,int num2calc,element_t** perm);
void update_perms(char c,int short_perm,int hdist);
void initPerm(element_t** perm);
int checkInp(char inp, mpz_t row, mpz_t col,mpz_t ox,mpz_t oy);
void printPermutation(element_t** perm);
void computeSpace(int hdist,element_t** perm,int short_perm,FILE *f);
float tsp_var_cost_function(element_t** solution);

/* globals */
element_t** perm; // create array of pointers to cities
tsp_problem_t *tsp_problem;

int main(int argc, char **argv) {

	/* init variables */
	int n=init(argc, argv,perm);

	/* init first permutation*/
	perm=(element_t**)(malloc(n*sizeof(element_t*)));
	for(int i=0;i<n;i++){
		perm[i]=(element_t*)malloc(n * sizeof(element_t));
		perm[i]->id=i;
		perm[i]->dir=-1;
	}

	/* init parameters
	 *
	 */
	printf("origin score: %f\n",tsp_var_cost_function(perm));
	mpz_t num_rows,num_col,ox,oy;
	mpz_init(num_rows);
	mpz_init(num_col);
	mpz_init(ox);
	mpz_init(oy);
	mpz_set_si(ox,0);
	mpz_set_si(oy,0);
	int short_perm= compute_space_dimensions(n, num_rows,num_col);
	tsp_problem->short_perm=short_perm;
	int hdist=100;// the size of the space to be rendered
	printf("shortperm:%d\n",short_perm);


	// init permutations for movement
	/*printf("backwards test\n");
	printPermutation(perm);
	JTn(short_perm,3,perm);//over1
	backwards(n,1,perm);//back
	printf("end backwards test\n");*/


	/* init first section
	 *
	 */
	initPerm(perm);
	float** scores= initSpace( hdist,perm,short_perm);
	//float* row;// to hold scores
	element_t** tmp=(element_t**)malloc(n* sizeof(element_t*));
	for(int i=0;i<n;i++)
		tmp[i]=(element_t*)malloc(sizeof(element_t));

	// inti files
	FILE *spacescores;
	FILE *statusf;
	FILE *inpf;

	char inp;
	int status;
	int validInp=0;

	// write initial space to spacescores file and set status
	spacescores=fopen(".spacescores.txt","w");
	for(int i=0;i<hdist;i++){
		for(int j=0;j<hdist;j++){
			fprintf(spacescores,"%f ",scores[i][j]);
		}
		fprintf(spacescores,"\n");
	}
	fclose(spacescores);
	statusf=fopen(".status.txt","w");
	fprintf(statusf,"%d",0);
	fclose(statusf);
	/* explore loop*/
	while(1){
		/* check status */
		statusf=fopen(".status.txt","r");
		status=fgetc(statusf);
		fclose(statusf);

		if(status=='1'){
			/*get keyboard input*/
			inpf=fopen(".inp.txt","r");
			inp=fgetc(inpf);
			printf("%c\n",inp);
			fclose(inpf);
			validInp=checkInp(inp,num_rows,num_col,ox,oy);
			if((inp^'\n')&& validInp){
				spacescores=fopen(".spacescores.txt","w");
				switch(inp){
				case 'a':// compute new left row
					 mpz_sub_ui (ox, ox,100);
					break;
				case 's':// compute new bottom row
					mpz_sub_ui (oy, oy,100);
					break;
				case 'w':// compute new top row
					mpz_add_ui (oy, oy,100);
					mpz_out_str (NULL, 10, oy);
					break;
				case 'd':// compute new right row
					mpz_add_ui (ox, ox,100);
					break;
				default://do nothing
					break;
				}
				update_perms(inp,short_perm,hdist);
				for(int i=0;i<n;i++)
					memcpy(tmp[i],tsp_problem->d[i],sizeof(element_t));
				forwards(tsp_problem->num_cities,1,tmp);
				computeSpace(hdist,tmp,short_perm,spacescores);
				fclose(spacescores);
			}else{
				if(!validInp)
					printf("\ninvalid inp\n");
			}
			statusf=fopen(".status.txt","w");
			fprintf(statusf,"%d",0);
			fclose(statusf);

		}
	}
	return 1;
}

void update_perms(char c,int short_perm,int hdist){
	switch(c){
	case 'a':
		backwards(short_perm,hdist+1,tsp_problem->u);
		backwards(short_perm,hdist+1,tsp_problem->d);
		backwards(short_perm,hdist+1,tsp_problem->l);
		backwards(short_perm,hdist+1,tsp_problem->r);
		break;
	case 's':
		backwards(tsp_problem->num_cities,hdist,tsp_problem->u);
		backwards(tsp_problem->num_cities,hdist,tsp_problem->d);
		backwards(tsp_problem->num_cities,hdist,tsp_problem->l);
		backwards(tsp_problem->num_cities,hdist,tsp_problem->r);
		break;
	case 'w':
		forwards(tsp_problem->num_cities,hdist,tsp_problem->u);
		forwards(tsp_problem->num_cities,hdist,tsp_problem->d);
		forwards(tsp_problem->num_cities,hdist,tsp_problem->l);
		forwards(tsp_problem->num_cities,hdist,tsp_problem->r);
		break;
	case 'd':
		forwards(short_perm,hdist+1,tsp_problem->u);
		forwards(short_perm,hdist+1,tsp_problem->d);
		forwards(short_perm,hdist+1,tsp_problem->l);
		forwards(short_perm,hdist+1,tsp_problem->r);
		break;
	default:
		break;
	}
	printf("corners:\n");
	printPermutation(tsp_problem->u);
	printPermutation(tsp_problem->d);
	printPermutation(tsp_problem->l);
	printPermutation(tsp_problem->r);
}

long int compute_space_dimensions(long int n, mpz_t num_rows,mpz_t num_col){
	// init
	mpz_t fact;
	mpz_init(fact);
	mpz_t rnf;
	mpz_init(rnf);
	mpz_t tmp;
	mpz_init(tmp);
	mpz_t diff;
	mpz_init(diff);


	mpz_fac_ui (fact, n);
	mpz_sqrt(rnf,fact);//round off decimal
	mpz_set(diff,fact);// init diff to somthing large

	long int count=1;
	do{
		mpz_set (tmp, diff);
		mpz_fac_ui(num_col,n-count);
		mpz_tdiv_q_2exp (num_col, num_col, 1);
		mpz_tdiv_q(num_rows,fact,num_col);
		mpz_sub(diff,num_col,num_rows);
		mpz_abs (diff, diff);
		//mpz_sub (diff, num_col, rnf);
		//mpz_abs (diff, diff);
		count++;

	}while(mpz_cmp(tmp,diff)>=0);
	// free variables
	mpz_clear(diff);
	mpz_clear(rnf);
	mpz_clear(tmp);

	long int short_perm = n-(count-2);
	// recompute the number skipped and the dimensions of the space
	mpz_fac_ui(num_col,short_perm);
	mpz_tdiv_q_2exp (num_col, num_col, 1);



	// assume that division results in whole numbers or round of is insignificant
	mpz_tdiv_q (num_rows, fact, num_col);

	//check that the space dimensions are accurate
	mpz_t fact_check;
	mpz_init(fact_check);
	mpz_mul (fact_check, num_rows, num_col);
	if( mpz_cmp(fact,fact_check)!=0){
		printf("error, the space does not have the number of solutions as n!\n");
	}
	mpz_clear(fact_check);
	mpz_clear(fact);

	// compute ratio
	mpf_t ratio_q,num_rows_f, num_col_f;
	mpf_init(ratio_q);
	mpf_init(num_rows_f);
	mpf_init(num_col_f);
	mpf_set_z(num_rows_f,num_rows);
	mpf_set_z(num_col_f,num_col);
	mpf_div(ratio_q,num_col_f,num_rows_f);
	double ratio_q_d=mpf_get_d (ratio_q);
	mpf_clear(num_rows_f);
	mpf_clear(num_col_f);
	mpf_clear(ratio_q);
	// print results
	/*
	printf("the number of soln skipped (dim1):\n");
	mpz_out_str(NULL,10,num_rows);
	printf("\n(num_col):\n");
	mpz_out_str(NULL,10,num_col);*/
	printf("\nthe ratio: %f\n",ratio_q_d);

	return short_perm;
}


int init(int argc,char **argv,element_t** perm){
	int num_cities;
	int opt = 0;
	/* read in the option line */
	opt = getopt(argc, argv, "n:");
	while(opt != -1)
	{
		switch(opt)
		{
			case 'n':
				sscanf(optarg,"%d",&num_cities);
				break;
			default :
				printf("Invalid arguments.\n");
				break;
		}

		opt = getopt(argc, argv, "n:");
	}



	/* init problem */
	tsp_init_problem(num_cities);
	printf("number of cities:%d",tsp_problem->num_cities);

	printf("Xmap = [");
	for (int i = 0; i < tsp_problem->num_cities; i++) {
		printf("%d ", tsp_problem->cities[i]->x);
	}
	printf("]\nYmap = [");
	printf("\n");

	for (int i = 0; i < tsp_problem->num_cities; i++) {
		printf("%d ", tsp_problem->cities[i]->y);
	}
	printf("\n");

	/* init first permutation*/
	perm=(element_t**)(malloc(num_cities*sizeof(element_t*)));
	for(int i=0;i<num_cities;i++){
		perm[i]=(element_t*)malloc(num_cities * sizeof(element_t));
		perm[i]->id=i;
		perm[i]->dir=-1;
	}

	return num_cities;
}

float** initSpace(int hdist,element_t** perm,int short_perm){
	// create 2d array for scores, these permutations need not be stored
	float** scores=(float**)malloc(hdist*sizeof(float*));
	element_t** tmp=(element_t**)malloc(tsp_problem->num_cities * sizeof(element_t*));
	for(int i=0;i<tsp_problem->num_cities;i++){
		tmp[i]=(element_t*)malloc(sizeof(element_t));
		memcpy(tmp[i],perm[i],sizeof(element_t));
	}

	for (int i=0;i<hdist;i++){

		scores[i]=(float*)malloc(hdist*sizeof(float));
		//printf("this is the perm that starts col:\n");
		//printPermutation(perm);
		scores[i]=JTn(tsp_problem->num_cities,hdist,perm);
		//move tmp over one, copy to perm
		forwards(short_perm,2,tmp);
		for(int j=0;j<tsp_problem->num_cities;j++){
			memcpy(perm[j],tmp[j],sizeof(element_t));
		}
	}

	/*for(int i=0;i<hdist;i++){
		for(int j=0;j<hdist;j++){
			printf("%f ",scores[i][j]);
		}
		printf("\n");
	}*/
	// set corners
	initPerm(tsp_problem->u);
	initPerm(tsp_problem->d);
	initPerm(tsp_problem->l);
	initPerm(tsp_problem->r);

	forwards(tsp_problem->num_cities,hdist+1,tsp_problem->u);
	//forwards(short_perm,2,tsp_problem->d);
	backwards(tsp_problem->num_cities,1,tsp_problem->d);
	backwards(short_perm,2,tsp_problem->l);
	forwards(short_perm,hdist*2+1,tsp_problem->r);

	printf("corners:\n");
	printPermutation(tsp_problem->u);
	printPermutation(tsp_problem->d);
	printPermutation(tsp_problem->l);
	printPermutation(tsp_problem->r);
	free(tmp);
	return scores;
}

void initPerm(element_t** perm){
	for(int i=0;i<tsp_problem->num_cities;i++){
		perm[i]->dir=-1;
		perm[i]->id=i;
	}
}
/*
 * Ñ Function: int mpz_cmp (const mpz_t op1, const mpz_t op2)
Ñ Function: int mpz_cmp_d (const mpz_t op1, double op2)
Ñ Macro: int mpz_cmp_si (const mpz_t op1, signed long int op2)
 */
int checkInp(char inp, mpz_t row, mpz_t col,mpz_t ox,mpz_t oy){
	switch(inp){
	case 'a':
		if(mpz_cmp_si(ox,0)>0)
			return 1;
		break;
	case 's':
		if(mpz_cmp_si(oy,0)>0)
			return 1;
		break;
	case'w':
		if(mpz_cmp(row,oy)>0)
			return 1;
		break;
	case 'd':
		if(mpz_cmp(col,ox)>0)
			return 1;
		break;
	default:
		return 0;
		break;
	}
	return 0;

}

void computeSpace(int hdist,element_t** perm,int short_perm,FILE *f){
	// create 2d array for scores, these permutations need not be stored
	float** scores=(float**)malloc(hdist*sizeof(float*));
	element_t** tmp=(element_t**)malloc(tsp_problem->num_cities * sizeof(element_t*));
	for(int i=0;i<tsp_problem->num_cities;i++){
		tmp[i]=(element_t*)malloc(sizeof(element_t));
		memcpy(tmp[i],perm[i],sizeof(element_t));
	}

	for (int i=0;i<hdist;i++){

		scores[i]=(float*)malloc(hdist*sizeof(float));
		scores[i]=JTn(tsp_problem->num_cities,hdist,perm);
		//move tmp over one, copy to perm
		forwards(short_perm,2,tmp);
		for(int i=0;i<tsp_problem->num_cities;i++){
			memcpy(perm[i],tmp[i],sizeof(element_t));
		}
	}

	for(int i=0;i<hdist;i++){
		for(int j=0;j<hdist;j++){
			fprintf(f,"%f ",scores[i][j]);
		}
		fprintf(f,"\n");
	}
	free(scores);
}

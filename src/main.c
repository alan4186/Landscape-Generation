#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

//#include <sys/time.h>

void JohnsonTrotter(int n, const char * c,int *d);

int main(int argc, char **argv) {
	int num_cities;
	const char * score_file;
	const char * citieschar;
	int * cities;
	int opt = 0;
	/* read in the option line */
	opt = getopt(argc, argv, "n:o:c:");
	while(opt != -1)
	{
		switch(opt)
		{
			case 'n':
				sscanf(optarg,"%d",&num_cities);
			break;
			case 'o':
				score_file = optarg;
			break;
			case 'c':
				citieschar= optarg;
				cities=(int*)malloc(sizeof(int)*20);
				for(int i=0;i<20;i++){
					cities[i]=(int)(citieschar[i]-48);
				}
				break;

			default :
				printf("Invalid arguments.\n");
				//print_usage();
			break;
		}

		opt = getopt(argc, argv, "n:o:c:");
	}
	printf("%d\t%s\t",num_cities, score_file);
	for (int i = 0;i<20;i++){
		printf("%d",cities[i]);
	}
	printf("\n");
	time_t start, stop;
	time(&start);
	JohnsonTrotter(num_cities, score_file,cities);
	time(&stop);

	double diff = difftime(stop,start);

	printf("time elapsed: %.f\n",diff);
}

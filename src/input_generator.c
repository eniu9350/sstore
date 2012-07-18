#include "input_generator.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


static void shuffle_int(int* data, int n)
{
				int temp;
				int i;
				int k1,k2;

				srand(n);
				for(i=0;i<n/2;i++)	{	//swap n/2 times
								k1 = rand()%n;
								k2 = rand()%n;

								temp = data[k1];
								data[k1] = data[k2];
								data[k2] = temp;
				}

				srand(n/2+5);
				for(i=0;i<n/2;i++)	{	//swap n/2 times
								k1 = rand()%n;
								k2 = rand()%n;

								temp = data[k1];
								data[k1] = data[k2];
								data[k2] = temp;
				}

				srand(n*2+5);
				for(i=0;i<n/2;i++)	{	//swap n/2 times
								k1 = rand()%n;
								k2 = rand()%n;

								temp = data[k1];
								data[k1] = data[k2];
								data[k2] = temp;
				}
}


//return "total" count of integers as durations
void generate_duration(int total, int* t_durations){
	int i;
	for(i=0;i<total;i++)	{
		t_durations[i] = 30;
		}
}


void generate_duration_old(int total, int* t_durations)
{
				duration* d;
				int i,j,k;
				double fsum;
				int nsum;
				int bound;
				int nmod = 5;//mmm: should be auto-adjusted
				long temp;

				d = (duration*)malloc(53*sizeof(duration));

				d[0].t = 1;
				d[0].f = pow(10,5.4);
				d[1].t = 2;
				d[1].f = pow(10,5.9);
				d[2].t = 3;
				d[2].f = pow(10,5.95);

				d[3].t = 4;
				d[3].f = pow(10,6);
				d[4].t = 5;
				d[4].f = pow(10,6);
				d[5].t = 6;
				d[5].f = pow(10,6);
				d[6].t = 7;
				d[6].f = pow(10,6);

				for(i=0;i<50-4;i++)	{
								d[7+i].t = pow(2, 3+i*0.2);
								d[7+i].f = pow(10,6)/pow(22.589, log(d[7+i].t/4));
				}

				for(i=0;i<53;i++)	{
								fsum += d[i].f;
				}

				for(i=0;i<53;i++)	{
								d[i].fint = total*d[i].f/fsum;
										printf("[%d]%d,%d\n", i, d[i].t, d[i].fint);
				}

				for(i=0;i<53;i++)	{
								if(d[i].fint == 0)	{
												bound = i;
												break;
								}
				}

				for(i=bound;i<53;i++)	{
								d[i].fint = 1;
								d[i%nmod].fint -= 1;	
							//			printf("[%d]%d,%d\n", i, d[i].t, d[i].fint);
				}


				nsum = 0;
				for(i=0;i<53;i++)	{
								nsum+=d[i].fint;
				}

				//distribute the residue
				for(i=0;i<total-nsum;i++)	{
								d[i%nmod].fint += 1;
				}


				//flat representation of durations
				k = 0;
				for(i=0;i<53;i++)	{
								for(j=0;j<d[i].fint;j++)	{
												t_durations[k++] = d[i].t;
								}
				}

				if(total!=k)	{
								printf("error before shuffling in duration generation process.\n");
				}

				//shuffle
				shuffle_int(t_durations, total);


				temp = 0;
				for(i=0;i<total;i++)	{
								temp += t_durations[i];
				}
				printf("avg dur = %f\n", temp*1.0f/total);
}

void generate_users(int total, user** users)
{
				int i;
				int* durations;
				//prepair durations
				durations = (int*)malloc(total*sizeof(int));
				generate_duration(total, durations);
				for(i=0;i<total;i++)	{
								users[i] = (user*)malloc(sizeof(user));
//								printf("sizeof user=%d\n", sizeof(user));
								users[i]->d = durations[i];
								//mmm: prepair user start time
								users[i]->a = i%120+5;
								sprintf(users[i]->id, "%d", i+1);
//printf("userid put=> %s\n", users[i]->id);
				}
}

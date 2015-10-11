#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

struct params{
             double left;
             double right;
             int num;            //номер шага
             double h;
             double S;
             };

double S;

void * thread_func(void *arg)
{
    struct params sin_func = *(struct params*)arg;

    double y_left = fabs(sin(sin_func.h* sin_func.num));
    double y_right = fabs(sin(sin_func.h * (sin_func.num + 1)));
    sin_func.S = (y_left+y_right) * sin_func.h / 2;
    S = S + sin_func.S;
//printf("S[%d]=%f  | y_left=%f  y_right=%f  h=%f\n",sin_func.num,sin_func.S,y_left,y_right,sin_func.h);
return 0;
}


int main(int arg, char **argv)
{
    int n = 0;
    double N = 0;
    S = 0;
    if(arg != 3)
    {
        printf("ERROR: неверное кол-во аргументов! \n");
        printf("Длина отрезка N = ");
        scanf("%lf",&N);
        printf("Разбиений     n = ");
        scanf("%d",&n);
    }
    else
    {
        N = atof(argv[1]);
        n = atoi(argv[2]);
    }

   if(n>300) //ограничение на кол-во потоков
   {
	printf("ERROR: кол-во разбиений не более 300! \n");
	n=300;
   }
    

//printf("-> N = %lf ; n = %d \n",N,n);
    pthread_t* thread = new pthread_t[n]; 
    struct params* trapeze = new struct params[n];

    for(int i =0; i < n; i++)	//создаем потоки
    {
	trapeze[i].num = i;
	trapeze[i].h = N/n;	//одинаков для всех
	if(pthread_create(&thread[i],NULL,&thread_func,&trapeze[i]) != 0)
	{
        	fprintf(stderr,"ERROR: pthread_create() \n");
		perror("pthread_create");
		return 1;
	}
        //printf(" i = %d | num = %d  h = %f \n",i,trapeze[i].num,trapeze[i].h);
    }

    for(int i=0;i<n;i++)
    {
	if(pthread_join(thread[i],NULL) != 0)
    	{
		fprintf(stderr,"ERROR: join() \n");
		perror("pthread_join");
		return 1;
	}
    }

printf("Integral function y=sin(x) = %f \n",S);

delete [] thread;
delete [] trapeze;

return 0; 
}

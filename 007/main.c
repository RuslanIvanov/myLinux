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

void * thread_func(void *arg)
{
    double left,right;
    struct params t = *(struct params*)arg;
/*
    left = sin_func.h * (sin_func.num - 1);
    right = sin_func.h * sin_func.num;
    double y_left = sin(left);
    double y_right = sin(right);
    sin_func.S = (y_left+y_right) * sin_func.h / 2;
*/
    t.S = 0;
//printf("num = %d h = %f \n",t.num,t.h);
   
return 0;
}


int main(int arg, char **argv)
{
    double S = 0;
    double N = 0;
    int n = 0;

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
printf("-> N = %lf ; n = %d \n",N,n);
 
    pthread_t thread[n]; 
    struct params trapeze[n];

    //создаем потоки 
    for(int i =0; i < n; i++)
    {
	trapeze[i].num = i;
	trapeze[i].h = N/n;	//одинаков для всех
	if(pthread_create(&thread[i],NULL,&thread_func,&trapeze[i]) != 0)
	{
        	fprintf(stderr,"ERROR: pthread_create() \n");
		return 1;
	}
printf(" i = %d | num = %d  h = %f \n",i,trapeze[i].num,trapeze[i].h);
    }

printf("MAIN FUNCTION!!!!!!!!!!! \n");

int status;
int res;
    for(int i=0;i<n;i++)
    {
printf("str77! \n");    	
	status =pthread_join(thread[i],(void **)&res);
printf("str79 status = %d ! \n",status);    	
	if(status != 0)
    	{
		fprintf(stderr,"ERROR: join() \n");
		return 1;
	}

printf("str84! \n");

    }
//double nnn = pthread_join(thread,(void **) &S_func);
//     if (pthread_join(thread,NULL)!=0)
   //  {
//         fprintf(stderr,"ERROR: join function\n");
//         return 1;
    // }
//printf("2 h = %f i = %d S_func = %f nnnnnnnn=%f \n",sin.h,sin.num,S_func,nnn);

for(int i=1;i<=n;i++)
{
printf("trapeze[%d].S = %f \n",i,trapeze[i].S);
}


return 0; 
}

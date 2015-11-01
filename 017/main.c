#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>

#define STACK_SIZE 10000

struct params{
             	double left;
             	double right;
             	int num;
             	double h;
             	double S;
		pid_t pid_clone;
             };

double S;

int thread_func(void *arg)
{
	struct params sin_func = *(struct params*)arg;
	double y_left = fabs(sin(sin_func.h* sin_func.num));
	double y_right = fabs(sin(sin_func.h * (sin_func.num + 1)));
	sin_func.S = (y_left+y_right) * sin_func.h / 2;
	
	struct params *p = (struct params*)arg;
	p->S = sin_func.S;
//printf("-> S[%d]=%f | l=%f right=%f h=%f\n",sin_func.num,sin_func.S,y_left,y_right,sin_func.h);
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
	//ограничение на кол-во клонов
	if(n>300)
	{
		printf("ERROR: кол-во разбиений не более 300! \n");
		n=300;
	}
    
	struct params* trapeze = new struct params[n];
	pid_t pid;
	char *stack;
	char *stackTop;
	stack = (char*)malloc(STACK_SIZE * n);
	stackTop = stack;

	for(int i =0; i < n; i++){
		trapeze[i].num = i;
		trapeze[i].h = N/n;	//одинаков для всех
		stackTop +=STACK_SIZE;
		pid = clone(thread_func,stackTop,CLONE_VM|SIGCHLD,&trapeze[i]);
		if(pid == -1)
			printf("error: clone() \n");
		trapeze[i].pid_clone = pid;
		//sleep(0.05);	//printf("i = %d  num = %d , h = %f pid = %d \n",i,trapeze[i].num,trapeze[i].h,pid);
	}

	int status;
	for(int i=0;i<n;i++){
		pid_t wpid = waitpid(trapeze[i].pid_clone,&status,0);
		//printf("num = %d pid = %d wpid=%d status = %d\n",i,trapeze[i].pid_clone,wpid,WEXITSTATUS(status));
	}	

	for(int i=0;i<n;i++){
		S +=trapeze[i].S;
		//printf("i = %d num = %d S = %f \n",i,trapeze[i].num,trapeze[i].S);
	}

printf("Площадь S = %f\n",S);
delete [] trapeze;
return 0; 
}

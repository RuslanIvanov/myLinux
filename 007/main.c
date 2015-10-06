#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

struct params{
             double left;
             double right;
             //double *result;
             };

void * thread_func(void *arg)
{

}


int main(void)
{
pthread_t thread;
int arg;

    int N = 0, n = 0;
    struct params *p;

    printf("Длина отрезка N = ");
    scanf("%d",&N);
    printf("Разбиений     n = ");
    scanf("%d",&n);
    printf("-> N = %d ; n = %d \n",N,n);

    for(int i =1; i <= n; i++)
    {

        p = new struct params;
        p->left = (N/n) * (i-1);
        p->right = (N/n) * i;  

printf(" left = %f  right = %f \n",p->left,p->right);

//int result =pthread_create(&thread,NULL,&thread_func,&arg);


delete p;
}
return 0; 
}


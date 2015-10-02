#include <stdio.h>
#include <string.h>
#include <signal.h>	//sigaction()

void function_handler(int s)
{
    fprintf(stderr,"\nGoodbye...\n");
    if (raise(SIGTERM) == -1)
        printf("ERROR: \n");
}

int main(void)
{
    struct sigaction act;

    act.sa_handler = &function_handler;  //функция-обработчик сигнала
    act.sa_flags = 0;                    //набор флагов
    sigemptyset(&act.sa_mask);           //обнуляем

    char command[BUFSIZ]="fffffff";
   
//    scanf("./%s",command);
gets(command);
    
printf("\n str20 ---> %s \n",command);

    if(sigaction(SIGINT,&act,NULL) == -1)
    {
        fprintf(stderr, "ERROR: functoin sigaction() \n");
        return 1;
    }

printf("str28 \n");



    while(1);

printf("str 34 \n");

    return 0; 
}


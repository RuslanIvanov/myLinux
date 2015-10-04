#include <stdio.h>
#include <string.h>
#include <signal.h>	//sigaction()

sig_atomic_t sig_flag= 0;

void handler_usr1(int s)
{
    sig_flag = 1;
}

void handler_usr2(int s)
{
    sig_flag = 2;
}

int main(void)
{
    struct sigaction act_usr1, act_usr2; //два действия пользователя

    sigemptyset(&act_usr1.sa_mask);      //обнуляем
    act_usr1.sa_handler = &handler_usr1; //функция-обработчик
    act_usr1.sa_flags = 0;               //набор флагов

    sigemptyset(&act_usr2.sa_mask);      //обнуляем
    act_usr2.sa_handler = &handler_usr2; //функция-обработчик
    act_usr2.sa_flags = 0;               //набор флагов
    
    char command[BUFSIZ];	//команда-файл вводимая пользователем
//    char dir[BUFSIZ];		//путь к файлу
   
    scanf("%s",command);

    
//printf("\n str20 ---> %s \n",command);

    if(sigaction(SIGINT,&act_usr1,NULL) == -1)
    {
        fprintf(stderr, "ERROR: sigaction() for act_usr1\n");
        return 1;
    }

    if(sigaction(SIGTTIN,&act_usr2,NULL) == -1)
    {
        fprintf(stderr,"ERROR: sigation() for act_usr2 \n");   
        return 1;
    }


printf("\n str20 ---> %s \n",command);

printf("str28 \n");

    while(1)
    {
        if(sig_flag == 1)
        { 
            fprintf(stderr,"\nGoodbye...\n");
            if (raise(SIGTERM) == -1)
                printf("ERROR: \n");
            sig_flag = 0;
        }
        
       if(sig_flag == 2)
       {
            printf(".....\n");
       
            sig_flag = 0;
       }
        
        

    } 



    return 0; 
}


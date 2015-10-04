#include <stdio.h>
#include <string.h>
#include <signal.h>	//sigaction()
//#include <stdlib.h>	//system()
#include <unistd.h>	//execl()
#include <sys/types.h>

sig_atomic_t sig_flag= 0;

void handler_usr1(int s)
{
    sig_flag = 1;
}

int main(void)
{
    char command[BUFSIZ];		 //команда пользователя
    pid_t result_proc;
                 
    struct sigaction act_usr1, act_usr2; //два действия пользователя
    sigemptyset(&act_usr1.sa_mask);      //обнуляем
    act_usr1.sa_handler = &handler_usr1; //функция-обработчик
    act_usr1.sa_flags = 0;               //набор флагов

    if(sigaction(SIGINT,&act_usr1,NULL) == -1)
    {
        fprintf(stderr, "ERROR: sigaction() \n");
        return 1;
    }

    while(1)
    {
        int r = scanf("%s",command);
        //printf("\n %d str20 ---> %s \n",r,command);
	if (r>0)	//введена команда
        {
            result_proc = fork();
	    if(!result_proc)
	    {
		//ex_args[0]=command;
		//printf("\n args[0]= %s \n",ex_args[0]);
		execlp(command,command,NULL);
		fprintf (stderr, "ERROR: function execlp() can't start process \n");
		return 1;
	    }  
            //system(command);

	}

        if(sig_flag == 1)
        { 
            fprintf(stderr,"\nGoodbye...\n");
            if (raise(SIGTERM) == -1)
                printf("ERROR: \n");
            sig_flag = 0;
        }
    } 
    return 0; 
}


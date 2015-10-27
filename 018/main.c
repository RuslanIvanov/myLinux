#include <stdio.h>
#include <string.h>
#include <signal.h>	//sigaction()
#include <unistd.h>	//execl()
#include <sys/types.h>
#include <syslog.h>

sig_atomic_t sig_flag= 0;

void handler_usr1(int s)
{
    sig_flag = 1;
}


void child()
{

openlog("demon", 0, LOG_USER);
syslog(LOG_NOTICE, "I am begin working",filename);
closelog();
        while(1)
	{
       		if(sig_flag == 1)
        	{
			fprintf(stderr,"\nGoodbye...\n");
			if (raise(SIGTERM) == -1)
				printf("ERROR: \n");
			sig_flag = 0;
	       	}
	}
}


int main(void)
{
	pid_t pid = fork();

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

	setsid();
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);


        if(pid == 0)
              child();
}

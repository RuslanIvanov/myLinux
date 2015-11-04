#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <poll.h>

int f_in,f_out;

void handler_usr(int s)
{
	printf("bye...\n");
	close(f_in);
	close(f_out);

	if (raise(SIGTERM) == -1)
        	printf("ERROR: \n");
}

int main(int arg,char **argv)
{
	struct sigaction act_usr;		//действия пользователя
	sigemptyset(&act_usr.sa_mask);		//обнуляем
	act_usr.sa_handler = &handler_usr;	//функция-обработчик
	act_usr.sa_flags = 0;               	//набор флагов
	
	if(sigaction(SIGINT,&act_usr,NULL) == -1)
	{
        	fprintf(stderr, "ERROR: sigaction() \n");
        	return 1;
	}

	if(arg != 3)   //если пользователь не ввел аргументы
	{
		fprintf(stderr,"ERROR: number arg is NULL! \n");
		printf("1 copy: ./poll name_1 name_2 \n");
		printf("2 copy: ./poll name_2 name_1 \n");
		exit(1);
  	}

	char *pipein = argv[1];
	char *pipeout = argv[2];
	//printf("in = %s out = %s \n",pipein,pipeout);
	if(access(pipein,0))
	{
		int in = mkfifo(pipein,0777);
		if(in == -1)
		{
			fprintf(stderr,"ERROR: Can`t create fifo_in: %s pp=%d \n",(char*)pipein,in);
			exit(1);
		}
	}
	if(access(pipeout,0))
	{
		int out = mkfifo(pipeout,0777);
		if(out == -1)
		{
			fprintf(stderr,"ERROR: Can`t create fifo_out: %s pp=%d \n",(char*)pipeout,out);
			exit(1);
		}
	}

	f_in = open(pipein, O_RDWR);
	if(f_in<0)
		printf("ERROR: open f_in\n");
	f_out = open(pipeout, O_RDWR);
	if(f_out<0)
		printf("ERROR: open f_out\n");
	
	//объявляем структуру для poll()
	struct pollfd fds[2];
	//определяем за какими событиями будем следить
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

      	fds[1].fd = f_in;
	fds[1].events = POLLIN;
	fds[1].revents = 0;

	int timeout = 5000;	//задержка ожидания события
	
	//printf("desc: %d %d\n",fds[0].fd,fds[1].fd);
	
	char buf[BUFSIZ];	//буфер для считывания потока stdin
        	
	while(true)
	{
        	//за какими 2-мя событиями будем следить
		int ready = poll(fds,2,timeout);
		//printf(" -----> poll: %d <----- \n",ready);
                if(ready)
                {
                        if(fds[0].revents & POLLIN)	//произошло событие в STDIN_FILENO
                        {
                              	if(fgets(buf,BUFSIZ,stdin) != 0)
				{
                                        int rez = 0;
                                        rez = write(f_out,buf,BUFSIZ);
                                        if(rez == -1)
						printf("Error: write f_out\n");
                                }
                        }

			if(fds[1].revents & POLLIN)	//произошло событие в f_in
			{
				int rez_in = read(f_in,buf,BUFSIZ);
                                if(rez_in == -1)
                                        printf("Error: read f_in\n");
                                printf("->%s",buf);
			}		
		}
	}
	return 0; 
}

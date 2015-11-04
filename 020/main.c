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

//int f_in,f_out;
struct pollfd fds[2];

void handler_usr(int s)
{
	printf("bye...\n");
	close(fds[0].fd);
	close(fds[1].fd);

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
		printf("1 copy: ./mychat name_1 name_2 \n");
		printf("2 copy: ./mychat name_2 name_1 \n");
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

	//f_in = open(argv[1], O_RDWR);
	//f_out = open(argv[2], O_RDWR);

        fds[0].fd = open(argv[1], O_RDWR);
	fds[0].events = POLLIN;

        fds[1].fd = open(argv[2], O_RDWR);
	fds[1].events - POLLIN;

printf("desc: %d %d\n",fds[0].fd,fds[1].fd);
	
	char buf[BUFSIZ];
        	
	while(true)
	{
	
		int ready = poll(fds,2,5000);
		//printf("poll:%d \n",ready);
		if(!ready) {
			printf("Nothing happened\n");
			continue;
		}


                if(ready)
                {
		
		}



/*
		FD_ZERO(&rd);			//инит структуру rd пустым множеством
		FD_SET(STDIN_FILENO,&rd);
		FD_SET(f_in,&rd);

		to.tv_sec = 5;

		int ready = select(10,&rd,NULL,NULL,&to);
		//if(!ready)
		//{
		//	printf("Error: select()\n");
		//	continue;
		//}
		//printf("select:%d \n",ready);
		if(ready)
		{
			if(FD_ISSET(STDIN_FILENO,&rd))
			{
                	        if(fgets(buf,BUFSIZ,stdin) != 0)
                        	{
                                	int rez = 0;
	                                rez = write(f_out,buf,BUFSIZ);
					if(rez == -1)
						printf("Error: write f_out\n");                                
                        	}
				//read(p1, buf, BUFSIZ);
				//printf("p1: have got %s\n",buf);
			}

			if(FD_ISSET(f_in,&rd))
			{
				int rez_in = read(f_in,buf,BUFSIZ);
				if(rez_in == -1)
					printf("Error: read f_in\n");
				printf("->%s\n",buf);
				//read(p2, buf, BUFSIZ);
				//printf("f_in: have got %s\n",buf);
			}
		}
*/
	}
	return 0; 
}

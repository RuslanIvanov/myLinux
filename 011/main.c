#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

//потоковая функция - слушает ввод с клавиатуры и 
//отправляет в поток pipeOUT
void * func_thread_out(void *arg)
{
	char * pipeout = (char*)arg;
	char buf[BUFSIZ];

	while(1)
	{
		if(scanf("%s",buf) > 0)
		{
	        	int fifo_out = open(pipeout,O_WRONLY);
	        	if(fifo_out == -1)
			{
        		        fprintf(stderr,"ERROR: Can`t open FIFO pipe_in %d \n",fifo_out);
                		exit(1);
	        
			}
  	        int wr_fifo = write(fifo_out,buf,BUFSIZ);
		if(wr_fifo == -1)
			fprintf(stderr,"ERROR: can`t write FIFO \n");
	       close(fifo_out);
		}
	}
}

int main(int arg,char **argv)
{
	pthread_t thread_out;
	char buf[BUFSIZ];

	if(arg == 1)   //если пользователь не ввел аргументы
	{
		fprintf(stderr,"ERROR: number arg is NULL! \n");
		printf("1 copy: ./mychat name_1 name_2 \n");
		printf("2 copy: ./mychat name_2 name_1 \n");
		exit(1);
  	}
  	else
  	{
//		sprintf(my_fifo.pipein,"/tmp/%s",argv[1]);
//		sprintf(my_fifo.pipeout,"/tmp/%s",argv[2]);
		char *pipein = argv[1];
		char *pipeout = argv[2];
//		printf("in = %s out = %s \n",pipein,pipeout);
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

        	if(pthread_create(&thread_out,NULL,&func_thread_out,pipeout) != 0)    //&my_fifo
        	{
			fprintf(stderr,"ERROR: pthread_create() FIFO in \n");
			return 1;
        	}

		while(1)
		{
		        int fifo_in = open(pipein,O_RDONLY);
                	if(fifo_in  == -1)
                        	fprintf(stderr,"ERROR: Can`t open FIFO %s = %d\n",pipein,fifo_in);
	                char buf[BUFSIZ];

        	        int read_fifo=read(fifo_in,&buf,BUFSIZ);
                	//if(read_fifo == -1)
			//	printf("can`t read FIFO \n");
			//else
			printf("%s\n",buf);
			close(fifo_in);
		}
	}	
return 0; 
}

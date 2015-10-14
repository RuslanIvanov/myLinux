#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

struct pipe
{
char pipein[BUFSIZ];
char pipeout[BUFSIZ];
char buf[BUFSIZ];
};

void * func_thread_out(void *arg)
{
printf ("out------- \n");
	struct pipe my_fifo = *(struct pipe*) arg;		//то что ввели, то в поток
	if(scanf("%s",my_fifo.buf) > 0)
	{
printf ("in str24-------\n");

	        int fifo_out = open(my_fifo.pipeout,O_WRONLY);
        	if(fifo_out == -1)
		{
        	        printf("ERROR: Can`t open FIFO pipe_in %s %d\n",my_fifo.pipeout,fifo_out);
                	exit(1);
	        
		}
printf ("in str33-------\n");

  	        int wr_fifo=write(fifo_out,my_fifo.buf,BUFSIZ);
		if(wr_fifo == -1)
			printf("ERROR: can`t write FIFO \n");
//	       close(fifo_out);
       }
}



void * func_thread_in(void *arg)
{
//printf ("in-------\n");
	struct pipe my_fifo = *(struct pipe*) arg;
	//while(1)
	{
		int fifo_in = open(my_fifo.pipein,O_RDONLY);
printf ("in str46-------\n");
		if(fifo_in  == -1)
                	printf("ERROR: Can`t open FIFO %s %d\n",my_fifo.pipein,fifo_in);
		char buf[BUFSIZ];
		
		int read_fifo=read(fifo_in,&buf,BUFSIZ);
		//if(read_fifo == -1)
//			printf("can`t read FIFO \n");
//           else
  			printf(" %s read_fifo=%d n",buf,read_fifo);
printf("str 55 \n");
//		close(fifo_in);

	}
}


int main(int arg,char **argv)
{
	struct pipe my_fifo;
	pthread_t thread_in, thread_out;
	char buf[BUFSIZ];

  if(arg == 1)   //если пользователь не ввел аргументы
  {
	printf("ERROR: number arg is NULL! \n");
	printf(" ./mychat fifoin fifoout \n");
	exit(1);
  }
  else
  {
	sprintf(my_fifo.pipein,"/tmp/%s",argv[1]);
	sprintf(my_fifo.pipeout,"/tmp/%s",argv[2]);

	if(access(my_fifo.pipein,0))
	{
		int in = mkfifo(my_fifo.pipein,0777);
		if(in == -1)
		{
			fprintf(stderr,"ERROR: Can`t create fifo %s pp=%d err=%d\n",my_fifo.pipein,in,errno);
			exit(1);
		}
	}
 	if(access(my_fifo.pipeout,0))
	{
		int out = mkfifo(my_fifo.pipeout,0777);
		if(out == -1)
		{
			printf("ERROR: Can`t create fifo %s pp=%d err=%d\n",my_fifo.pipeout,out,errno);
			exit(1);
		}
	}

	while(1)
	{
		if(pthread_create(&thread_in,NULL,&func_thread_in,&my_fifo) != 0)    //&my_fifo
		{
			fprintf(stderr,"ERROR: pthread_create() FIFO in \n");
			return 1;
		}

		if(pthread_create(&thread_out,NULL,&func_thread_out,&my_fifo) != 0)
                {       
                        fprintf(stderr,"ERROR: pthread_create() FIFO out \n");
                        return 1;
                }
		pthread_join(thread_in,NULL);
		pthread_join(thread_out,NULL);
	}
  }   
return 0; 
}

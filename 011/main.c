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
	char *pipeout = (char*) arg;		//то что ввели, то в поток
//printf ("out-------%s \n",pipeout);

	char buf[BUFSIZ]={'\0'};
if(fgets(buf, BUFSIZ, stdin) != 0)
printf ("out-------%s \n",buf);
/*
	int f = (scanf("%s",my_pipe.buf));

        if(f>0)
	{
            int fifo_out = open(my_pipe.pipeout,O_WRONLY);
            if(fifo_out == -1)
            {
                printf("ERROR: Can`t open FIFO pipe_in %s %d\n",my_pipe.pipeout,fifo_out);
                exit(1);
            }
       int wr_fifo=write(fifo_out,my_pipe.buf,BUFSIZ);
       if(wr_fifo == -1)
       {
            printf("can`t write FIFO \n");
//            break;
       }
       close(fifo_out);
       }
*/


}




void * func_thread_in(void *arg)
{
	char *pipein = (char*) arg;
printf ("in-------%s \n",pipein);



/*
       int fifo_in = open(my_pipe.pipein,O_RDONLY);
       if(fifo_in == -1)
       {
           printf("ERROR: Can`t open FIFO %s %d\n",my_pipe.pipein,fifo_in);
       }

char buf[BUFSIZ];

int read_fifo=read(fifo_in,&buf,BUFSIZ);
           if(read_fifo == -1)
               printf("can`t read FIFO \n");
           else
               printf(" %s \n",buf);





close(fifo_in);

*/
}


int main(int arg,char **argv)
{

struct pipe my_fifo;
//  char pipein[BUFSIZ];
//  char pipeout[BUFSIZ];

  pthread_t thread_in, thread_out;
  char *name_in,*name_out;		//имена потоков 

  if(arg == 1)   //если пользователь не ввел аргументы
  {
	printf("ERROR: number arg is NULL! \n");
	printf(" ./mychat fifoin fifoout \n");
	exit(1);
  }
  else
  {
	name_in = argv[1];	//pipein
	name_out = argv[2];	//pipeout
	//sprintf(my_fifo.pipein,"/tmp/%s",argv[1]);
	//sprintf(my_fifo.pipeout,"/tmp/%s",argv[2]);

	if(access(name_in,0))
	{
		int in = mkfifo(name_in,0777);
		if(in == -1)
		{
			fprintf(stderr,"ERROR: Can`t create fifo %s pp=%d err=%d\n",name_in,in,errno);
			exit(1);
		}
	}
 	if(access(name_out,0))
	{
		int out = mkfifo(name_out,0777);
		if(out == -1)
		{
			printf("ERROR: Can`t create fifo %s pp=%d err=%d\n",name_out,out,errno);
			exit(1);
		}
	}

	while(1)
	{
		if(pthread_create(&thread_in,NULL,&func_thread_in,name_in) != 0)    //&my_fifo
		{
			fprintf(stderr,"ERROR: pthread_create() FIFO in \n");
			return 1;
		}
		if(pthread_create(&thread_out,NULL,&func_thread_out,name_out) != 0)
                {       
                        fprintf(stderr,"ERROR: pthread_create() FIFO out \n");
                        return 1;
                }
//		pthread_join(thread_in,NULL);
//		pthread_join(thread_out,NULL);
	}
              pthread_join(thread_in,NULL);
              pthread_join(thread_out,NULL);
}   
return 0; 
}

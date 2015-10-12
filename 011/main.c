#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <fcntl.h>

//#define FIFO_IN		"pipeinllll"
//#define FIFO_OUT	"pipeout"

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  char pipein[BUFSIZ];
  char pipeout[BUFSIZ];

  int fifo_in,fifo_out;
  pid_t pid_in,pid_out;

  char buf[BUFSIZ];	//буфер
  char *p_buf=buf;

  char buffer[]="dskfdslkjfds\n";

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR: number arg is NULL! \n");
     exit(1);
  }
  else
  {
      sprintf(pipein,"/%s",argv[1]);
      sprintf(pipeout,"/%s",argv[2]);

      unlink(pipein);
      unlink(pipeout);

      if(mkfifo(pipein, O_RDWR) == -1)    //создание FIFO
      {
          fprintf(stderr,"ERROR: Can`t create fifo \n");
          exit (1);
      }

      pid_in=fork();	//процесс читает
      if(pid_in == -1)
      {
          perror("fork()");
          exit (1);
      }
      else if(pid_in > 0)
      {
          fifo_in = open(pipein,O_RDONLY);
          if(fifo_in == -1)
          {
              fprintf(stderr,"ERROR: Can`t open fifo \n");
              exit (1);
          }
          
          int read_fifo=read(fifo_in,&buf,BUFSIZ);
          if(read_fifo == -1)
              printf("can`t read FIFO \n");
          else
              printf(" %s \n",buf);
          close(fifo_in);
/*    while(1)
      {
      scanf("%s",buf);
      fscanf(fifo,"%s",p_buf);  }
*/
       }

       if(mkfifo(pipeout, O_RDWR) == -1)    //создание FIFO
       {
           fprintf(stderr,"ERROR: Can`t create fifo \n");
           exit (1);
       }
 
       pid_out=fork();    //процесс пишет
       if(pid_out == -1)
       {
           perror("fork()");
           exit (1);
       }
       else if(pid_out > 0)
       {
           fifo_out = open(pipeout,O_WRONLY);
           if(fifo_in == -1)
           {
               fprintf(stderr,"ERROR: Can`t open fifo \n");
               exit (1);
           }
           while(fgets(buffer,sizeof(buffer),stdin) != NULL)
           {
               int wr_fifo=write(fifo_out,buffer,sizeof(buffer));
               if(wr_fifo == -1)
               {
                   printf("can`t write FIFO \n");
                   break;
               }
           }
           close(fifo_out);
       }


  }   
return 0; 
}

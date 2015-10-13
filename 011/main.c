#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <fcntl.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  //FILE *fifo_in;
  char pipein[BUFSIZ];
//  char pipeout[BUFSIZ];

//  int fifo_in,fifo_out;
//  pid_t pid_in,pid_out;

  char buf[BUFSIZ];	//буфер
  char *p_buf;

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR: number arg is NULL! \n");
     printf(" ./mychat fifoin fifoout \n");
     exit(1);
  }
  else
  {
      sprintf(pipein,"%s",argv[1]);
//      sprintf(pipeout,"/tmp/%s",argv[2]);
//mkfifo(topin,  O_RDWR|S_IFIFO|S_IRWXU|S_IRWXG|S_IRWXO);
      if(mkfifo(pipein, O_RDONLY) == -1)    //создание FIFO_IN
      {
          fprintf(stderr,"ERROR: Can`t create fifo \n");
          return (1);
      }
    
      int fifo_in = open(pipein,O_RDONLY | O_NONBLOCK);
      if(fifo_in <0)
      {
          fprintf(stderr,"ERROR: Can`t open FIFO %s \n",pipein);
          exit(1);
      }

close(fifo_in);

/*
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
//    while(1)
//    {
 //     scanf("%s",buf);
 //     fscanf(fifo,"%s",p_buf);  }

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
           while(fgets(buf,BUFSIZ,stdin) != NULL)
           {
               int wr_fifo=write(fifo_out,buf,BUFSIZ);
               if(wr_fifo == -1)
               {
                   printf("can`t write FIFO \n");
                   break;
               }
           }
           close(fifo_out);
       }
*/

  }   
return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>

#define FIFO_IN		"pipeinllll"
#define FIFO_OUT	"pipeout"

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  FILE *fifo;

  char buf[BUFSIZ];	//буфер
  char *p_buf=buf;

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR: number arg is NULL! \n");
     exit(1);
  }
  else
  {
  
      unlink(FIFO_IN);
      if(mkfifo(FIFO_IN, O_RDWR) == -1)
      {
          fprintf(stderr,"ERROR: Can`t create fifo \n");
          exit 1;
      }
      fifo = fopen(FIFO_IN,O_RDWR);
      if(fifo == -1)
      {
          fprintf(stderr,"ERROR: Can`t open fifo \n");
          return 1;
      }
char wr_buf[]="приприприпри ри прии";
char rd_buf[BUFSIZ];
write(fifo,wr_buf,strlen(wr_buf));

int ttt=read(fifo,rd_buf,sizeof(rd_buf));

if(ttt == -1)
{
printf("невозможно прочесть из FIFO \n");
}
else
printf("Прочитано из FIFO = %s \n",rd_buf);

/*
      while(1)
      {
      scanf("%s",buf);
         fscanf(fifo,"%s",p_buf);
      
      }
      fclose(fifo);
*/


  }   
return 0; 
}

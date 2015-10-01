#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент

  if(arg != 3)   //если пользователь ввел не три аргумента
  {
     printf("ERROR: check amount of arguments! \n");
     exit(1);
  }
  
  int pid = atoi(argv[1]);	//код процесса
  int sign = atoi(argv[2]);	//код сигнала
  
  if(sign == SIGTERM )          //только 15 сигнал
  {
     if(kill(pid,sign) == -1)
     {
        printf("ERRROR: can't send signal! \n");
        return 1;
     }
  }
return 0; 
}


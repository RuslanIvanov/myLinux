#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент

  if(arg != 3)   //если пользователь ввел не три аргумента
  {
     printf("ERROR! check amount of arguments \n");
     exit(1);
  }
  
  int pid = atoi(argv[1]);	//код процесса
  int sign = atoi(argv[2]);	//код сигнала

//printf("error: pid=%d ppid=%d \n",pid_code,ppid_code);
  
printf("pid = %d sign = %d  \n",pid,sign);

  

return 0; 
}


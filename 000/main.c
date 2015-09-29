#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент

//printf("ERROR: кол-во аргументов NULl! %d %d \n",arg,atoi(argv[0]));
  
  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }
  
  int pid = atoi(argv[1]);	//код процесса
  int sign = atoi(argv[2]);	//код сигнала

//printf("error: pid=%d ppid=%d \n",pid_code,ppid_code);
  
printf("-------%s \n %s \n",buf,tree_pid);
  

return (1); 
}


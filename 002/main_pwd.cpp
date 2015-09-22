#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int c, char **v, char **env)
{

printf(" %d %p %p \n",c,v,env);

//печать pwd через функцию getenv
if(*env)
{
  char *cur_dir = getenv ("PWD");
  printf("CURRENT PATH of getevn functions: %s \n",cur_dir);
}

//печать pwd, прочтением переменных массива функции main

while(*env)
{
  char *p = strstr(*env,"PWD=");
  if(p==*env)
    printf("CURRENT PATH of main functions: %s \n",(p+4));
  env++;
}

return 0;
}

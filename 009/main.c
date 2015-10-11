#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  FILE *my_pipe;

  char cmd[BUFSIZ];	//команда пользователя
  char *p_cmd=cmd;
  char buf[BUFSIZ];	//строка потока

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }
  else
  {
     for(int i=1;i<arg;i++)
     {
         p_cmd= strcat(cmd,argv[i]);
         p_cmd = strcat (cmd," ");
     }
     //printf("arg = %d p_cmd = %s \n",arg,cmd);     
  }
  
  if (! (my_pipe = popen(cmd,"r")))
      exit (1);

  while (fgets(buf,sizeof(buf),my_pipe))
  {
    int N = strlen(buf);
    for(int i=0;i<N/2;i++)
    {
        char p;
        p = buf[i];
        buf[i]=buf[N-i-1];
        buf[N-i-1]=p;
    }
    printf("%s",buf);
  }
  printf("\n");
  
  pclose(my_pipe);
return 0; 
}

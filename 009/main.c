#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  char cmd[BUFSIZ];
  char buf[BUFSIZ];
  FILE *my_pipe;

  char *p_cmd;

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }
  else
  {
     p_cmd=cmd;
     for(int i=1;i<arg;i++)
     {
     p_cmd = strcpy(p_cmd,argv[i]);
     p_cmd = strcpy (p_cmd," ");
     }
printf("arg = %d cmd = %s \n",arg,p_cmd);     
 
/*    if(arg>2)	// если аргументов больше одного ./my_pipe-0 ls-1 -a-2
     {
        char *p_cmd;
	for(int i = 2; i <= arg; i++)
	{
		p_cmd=strcat(p_cmd," ");
		p_cmd=strcat(p_cmd,argv[i]);

printf("i=%d arg=%d cmd = %s \n",i,arg,p_cmd);     

	}

     }
*/
  }

//printf("%d cmd = %s \n",arg,cmd);     
  
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

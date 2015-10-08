#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  char cmd[BUFSIZ];
  char buf[BUFSIZ];
  FILE *my_pipe;

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }
  else
  {
     strcpy(cmd,argv[1]);
printf("arg = %d cmd = %s \n",arg,cmd);     
     if(arg>2)	// если аргументов больше одного
     {int i = 2;
	while(i<=arg)
	{
		strcat(cmd," ");
		strcat(cmd,argv[i]);
i++;
	}
//	for(int i=2;i<=arg;i++)
//	{
//strcat(cmd," m");
//strcat(cmd,argv[i]);
//sprintf(cmd,"%s",argv[i]);
//	}
     }
  }


printf("%d cmd = %s \n",arg,cmd);     

  
  if (! (my_pipe = popen(argv[1],"r")))
      exit (1);

  while (fgets(buf,sizeof(buf),my_pipe))
  {
    int N = strlen(buf);
    char my_buf[N];
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

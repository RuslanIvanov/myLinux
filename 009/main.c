#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  char buf[BUFSIZ];
  FILE *my_pipe;

  if(arg == 1)   //если пользователь ничего не ввел
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }


  
  if (! (my_pipe = popen(argv[1],"r")))
      exit (1);

  while (fgets(buf,sizeof(buf),my_pipe))
  {
    printf("buf = %s \n",buf);
    int N = strlen(buf);
    int i;
    for(i=0;i<N;i++)
    {
    char p;
   p = buf[i];
 buf[i]=buf[N-i-1];
 buf[N-i-1]=p;
printf("%s",&buf[i]);

}

    printf("buf = %s \n",buf);


}


pclose(my_pipe);


return 0; 
}


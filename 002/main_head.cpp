#include <stdio.h>
#include <string.h>

extern "C" int HelloWorld(char *)
{
return 0;
}

int main(int c, char **v, char **env)
{

printf("c = %d  args = %p  env = %p \n",c,v,env);

while(*env)
{
  char *p = strstr(*env,"PWD=");
  if(p==*env)
     printf("current path = %s \n",(p+4));
  env++;
}

return 0;
}

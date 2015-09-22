#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int c, char **v, char **env)
{

printf(" %d %p %p \n",c,v,env);

/*
if(!name_dir)
{
  return 0;
}
*/

//char *vvv = name_dir[0];
//while(*env)
//{
//printf(" %s \n",v);
//}

if(*env)
{
char *cur_dir = getenv ("PWD");
printf("%s \n %s\n",cur_dir,cur_cwd);
}
//env++;

//}

return 0;

}

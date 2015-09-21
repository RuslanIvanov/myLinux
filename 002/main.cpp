#include <stdio.h>
#include <stdlib.h>

int main ()
{
char **name_dir;

if(!name_dir)
  return;

char *v = name_dir[0];
while(v)
{
printf(" %s \n",v);
}

//char *s;
//s = getenv ("PWD");
//printf("%s \n",s);
//return 0;




}

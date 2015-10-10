#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{				//argv - ук на аргумент

char buf[BUFSIZ];
int i=0;

while(fgets(buf,BUFSIZ,stdin))
{
i++;
fputs(buf,stdin);

printf("buf = %s \n",buf);
}

printf("count = %d\n", i);


return 0; 
}


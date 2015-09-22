#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int c,char **v)
{
  FILE *file_st;
  char name_dir[BUFSIZ];
  int pid_code = atoi(v[1]);

  sprintf(name_dir,"/proc/%d/status",pid_code);
  
  file_st = fopen(name_dir,"r");
  if(!file_st)
  {
  printf("error! open file \n");
  return (1);
  }

  char string_st[20];
  int i=0;
  size_t result;

  while(fgets(string_st,sizeof(string_st),file_st))
  {
    result =strlen(string_st);
    	
    printf("String %d %ld \n",i++,result	);
  } 
  fclose(file_st);

return (1); 
}


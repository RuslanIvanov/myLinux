#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int parent_pid(int pid_code)
{
  FILE *file_st;
  char name_dir[BUFSIZ];  //имя файла с путем

  sprintf(name_dir,"/proc/%d/status",pid_code);
  
  file_st = fopen(name_dir,"r");
  if(!file_st)
  {
  printf("ERROR! can`t open file \n");
  return (1);
  }

  char string_st[20];
  char buf_ppid[4];

  int i=0;
  int result;
  int num_ppid =0;

  while(fgets(string_st,sizeof(string_st),file_st))
  {
    result =strlen(string_st);
    if (strstr(string_st,"PPid"))   //нашел прародителя
	{ 
          strcpy(buf_ppid,&string_st[6]);
          num_ppid = atoi(buf_ppid);
// printf("НАШЕЛ!!!!!!!!!!!! длинна строки =%d \n %s \n число ppid = %d \n", result,buf_ppid,num_ppid);
break;
	}	
   // printf("String %d - %s  \n",i++,string_st);
  }

 
  fclose(file_st);

return num_ppid;
}


int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  char tree_pid[BUFSIZ];  //дерево процесса

//printf("ERROR: кол-во аргументов NULl! %d %d \n",arg,atoi(argv[0]));
  
  if(arg == 1)   //если пользователь ничего не ввел, аргумент только один
  {
     printf("ERROR! number arg is NULL! \n");
     exit(1);
  }
  
  int pid_code = atoi(argv[1]);
  int ppid_code = 0;
 // ppid_code = parent_pid(pid_code);
  
//printf("error: pid=%d ppid=%d \n",pid_code,ppid_code);
  
   sprintf(tree_pid,"--%d",pid_code);
  char buf[10]; 
  while(pid_code)
{

   ppid_code = parent_pid(pid_code);


    sprintf(buf,"--%d",ppid_code);

    strcat(tree_pid,buf);
    
//printf("-------%s \n %s \n",buf,tree_pid);
  
    pid_code = ppid_code;
  }

printf("-------%s \n %s \n",buf,tree_pid);
  

return (1); 
}


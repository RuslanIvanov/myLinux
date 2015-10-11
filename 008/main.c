#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

//функция поиска tgid
int read_task(int pid_user,int pid_dir)
{

  FILE *file_st;
  char name_file[BUFSIZ];  //имя файла с путем

  sprintf(name_file,"/proc/%d/task/%d/status",pid_user,pid_dir);
  //printf("----%s \n",name_file);

  file_st = fopen(name_file,"r");
  if (!file_st)
  {
     printf("ERROR! can`t open file \n");
     exit (1);
  }
  char string_st[20];
  char buf_pid[10];            //для PID 10 символов
  char buf_tgid[10];
  int i=0;
  while (fgets(string_st,sizeof(string_st),file_st))
  {
      if (strstr(string_st,"Tgid"))
         strcpy(buf_tgid,&string_st[6]);
      else
      if (strstr(string_st,"Pid"))   //нашел PID
      {
         strcpy(buf_pid,&string_st[5]);
         break;
      }      
  }
  fclose(file_st);
  //печать, если PID это процесс
  if(pid_user == atoi(buf_tgid))
  {    
      if(pid_user != atoi(buf_pid))
	printf("   L %s",buf_pid);
  }
  else
        return (atoi(buf_tgid));
return 0;
}

//функция печати дерева потоков TGID  для процесса PID
int tree_proc(int pid_user)
{
  DIR *dir;
  struct dirent *entry;
  char name_dir[BUFSIZ]; 
  
  sprintf(name_dir,"/proc/%d/task/",pid_user);	//папка с потоками
  //printf("name_dir=%s \n",name_dir); 
  dir = opendir(name_dir);
  if(!dir)
  {
	perror("ERROR: diropen");
        exit(1);
  };
  printf("%d\n",pid_user);
  int result =0;
  while ( (entry = readdir(dir)) != NULL )	//читаем каталог
  {
     if (atoi(entry->d_name))
	result = read_task(pid_user,atoi(entry->d_name));
     if(result !=0)
     {
        printf("this is thread process PID = %d \n",result);
        exit(1);
     }
  };
  closedir(dir);
return 0;
}

// чтение всех процессов дирректории ./proc
int tree_proc_all()
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc/");
    if (!dir) 
    {
        perror("diropen");
        exit(1);
    };
    while ( (entry = readdir(dir)) != NULL )
    {
	if (atoi(entry->d_name))
		tree_proc(atoi(entry->d_name));
    };
    closedir(dir);
return 0;
}


int main(int arg,char **argv)
{			
    if(arg == 1)		//пользователь ничего не ввел
    {
    	printf("ERROR: аргументов NULl!\n");
  	tree_proc_all();		//вызываем по всем процессам
    }
    else if (arg == 2)   	//второй аргумент = PID процесса
	tree_proc(atoi(argv[1]));
    else
	printf("ERROR: проверьте количество аргументов %d !\n",arg);
return 0;
} 

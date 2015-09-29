#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

//функция поиска родителя
int parent_pid(int pid_code)
{
  FILE *file_st;
  char name_dir[BUFSIZ];  //имя файла с путем

  sprintf(name_dir,"/proc/%d/status",pid_code);
  
  file_st = fopen(name_dir,"r");
  if (!file_st)
     {
     printf("ERROR! can`t open file \n");
     exit (1);
     }

  char string_st[20];
  char buf_ppid[4];
  int  num_ppid =0;

  while (fgets(string_st,sizeof(string_st),file_st))
      {
      if (strstr(string_st,"PPid"))   //нашел прародителя
         { 
         strcpy(buf_ppid,&string_st[6]);
         num_ppid = atoi(buf_ppid);
         //printf("НАШЕЛ!!!!!!!!!!!! ppid = %d \n", num_ppid);
         break;
	 }	
      }
  
  fclose(file_st);

return num_ppid;
}

//функция формирования дерева родителей процесса
int print_tree(int pid_code)
{
  char tree_pid[BUFSIZ];  //дерево процесса
  char buf[10];           //вспомогательный буфер
  int  ppid_code = 0;     //родитель

  sprintf(tree_pid,"%d",pid_code);
  while(pid_code)
  {
      ppid_code = parent_pid(pid_code);   //получаем родителя
      sprintf(buf," --> %d",ppid_code);
      strcat(tree_pid,buf);
      pid_code = ppid_code;

      if(!ppid_code) //нашли родителя 0
         printf(" * %s \n",tree_pid);
  }
return 0;
}

// чтение всех процессов дирректории ./proc
int dir_proc()
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
            print_tree(atoi(entry->d_name));
    };

    closedir(dir);

return 0;
}


int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
//printf("ERROR: кол-во аргументов NULl! %d %d \n",arg,atoi(argv[0]));
  
  if(arg == 1)         //аргумент только один, пользователь ничего не ввел
     dir_proc();       //вызываем по всем процессам
  else if (arg == 2)   //второй аргумент - это pid процесса введенное пользователем
           print_tree(atoi(argv[1]));
  else
     printf("ERROR: проверьте количество аргументов %d !\n",arg);

return 0;
} 

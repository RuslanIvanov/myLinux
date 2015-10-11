#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg, char **argv)
{
    FILE *my_file;

    char buf[BUFSIZ];
    char *p_buf = buf;

    int  num_find = 0; 

    if(arg != 3)
    {
        printf("ERROR: check amount of arguments! \n");
        exit(1);
    }

    my_file = fopen(argv[2],"w");	//создаем файл для записи
    if(!my_file)
    {
        printf("ERROR: can`t open/create file! \n");
        exit(1);
    }

    while(fgets(buf,BUFSIZ,stdin))	//читаем строку из потока в stdin
    {
       fputs(buf, stdout);		//записываем строку в поток stdout
       if(strstr(p_buf,argv[1]))        //ищем в строке
       {
           num_find++;
           //fprintf(my_file,"%s\n",p_buf);
       }
    }
    //printf("buf = %s num = %d \n",buf,num_find);
    if(num_find)
        fprintf(my_file,"The word '%s' are found %d ps\n",argv[1],num_find);
    else
        fprintf(my_file,"The word '%s' isn't found\n",argv[1]);

    fclose(my_file);
  
return 0; 
}

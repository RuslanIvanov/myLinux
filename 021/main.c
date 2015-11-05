#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

static int sort_func(const void *a, const void *b)
{
	return(strcmp((const char*)a,(const char*)b));
//return strcmp(a,b);
//return (1);
}

void error_arg()
{
	printf("Error number arguments \n");
	printf("format: ./mmsort  file_name  size_sort\n");
}

int main(int arg,char **argv)
{
	if(arg != 3)
	{
		error_arg();
		exit(1);
	}
  
	//int pid = atoi(argv[1]);	//файл
	int size_sort = atoi(argv[2]);	//размер сортировки

	int f_sort;
	char *file_memory;

	struct stat statbuf;
	//открываем файл
	f_sort = open(argv[1],O_RDWR,0666);
	if(f_sort < 0)
	{
		printf("Error open() file\n");
		exit(1);
	}
	//определяем размер файла
	if(fstat(f_sort,&statbuf) < 0)
	{
		printf("Error fstat()\n");
		exit(1);
	}

	file_memory = (char*)mmap(0,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,f_sort,0);
	if(file_memory == MAP_FAILED)
	{
		printf("Error mmap()\n");
		exit(1);
	}
	close(f_sort);

    qsort(file_memory, statbuf.st_size, size_sort, sort_func);

    munmap(file_memory, statbuf.st_size);
    return 0;




return 0; 
}

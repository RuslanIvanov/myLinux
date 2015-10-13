#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


const char *name = "./dd";

int main()
{
	
	int f = mkfifo(name,O_CREAT|O_RDWR);
	

	int p = open("./a", O_RDONLY);
	printf("%d %d\n",errno,p);
	return 0;
}

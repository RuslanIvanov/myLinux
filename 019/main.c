#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//mkfifo
#include <sys/stat.h>	//mkfifo
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int main(int arg,char **argv)
{
	fd_set rd;
	char buf[BUFSIZ];
	struct timeval to = { 5 , 0 };
	int ready = 0;

	if(arg != 3)   //если пользователь не ввел аргументы
	{
		fprintf(stderr,"ERROR: number arg is NULL! \n");
		printf("1 copy: ./mychat name_1 name_2 \n");
		printf("2 copy: ./mychat name_2 name_1 \n");
		exit(1);
  	}
  	else
  	{
//		printf("in = %s out = %s \n",argv[1],argv[2]);

		int p1 = open(argv[1], O_RDWR);
		int p2 = open(argv[2], O_RDWR);
		
		printf("desc: %d %d\n",p1,p2);


		while(true)
		{

			FD_ZERO(&rd);
			FD_SET(p1,&rd);
			FD_SET(p2,&rd);

			to.tv_sec = 5;

			ready = select(10,&rd,NULL,NULL,&to);
printf("select:%d \n",ready);
 
		if(!ready){
			printf("Nothing happened\n");
			continue;
		}

		if(FD_ISSET(p1,&rd)){
			read(p1, buf, BUFSIZ);
			printf("p1: have got %s\n",buf);
		}

		if(FD_ISSET(p2,&rd)) {
			read(p2, buf, BUFSIZ);
			printf("p2: have got %s\n",buf);
		}





		}
	}	
return 0; 
}

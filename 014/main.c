#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//socket
#include <sys/socket.h>	//socket
#include <sys/un.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int sock;
int myport;

void * func_thread(void *arg)
{

	struct sockaddr_in addr;
	char buf[BUFSIZ];

	memset(&addr, 0, sizeof(addr));
	//определяем параметры соединения
	addr.sin_family = AF_INET;
	addr.sin_port = htons(myport);			//отправляем
	addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);   //ВСЕМ!

	int broadcast =1;
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof broadcast);

	while(1)
	{
//		printf("send message : ");	
		if(scanf("%s",buf) > 0)
		{
//			printf("послыаем buf = %s port = %d sock = %d \n",buf,myport,sock);		
               		int send = sendto(sock,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
			if(send == -1)
				fprintf(stderr,"ERROR: sendto() thread \n");
		}
	}

}

int main(int arg,char **argv)
{
	pthread_t thread;
	char buf[BUFSIZ];

	struct sockaddr_in addr;

	if(arg != 2)   //если пользователь не ввел аргументы
	{
		fprintf(stderr,"ERROR: number arg! \n");
		printf("./broadcast port \n");
		exit(1);
  	}
  	else
  	{
		myport = atoi(argv[1]);
//printf("myport = %d \n",myport);
		//создаем сокет
 		sock = socket(AF_INET,SOCK_DGRAM,0);
		if(sock == -1)
		{
			fprintf(stderr,"ERROR: socket() error \n");
			exit(1);
		}
        	
		memset(&addr, 0, sizeof(sockaddr_in));		
		//определяем параметры соединения
		addr.sin_family = AF_INET;
		addr.sin_port = htons(myport);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);	//слушаем ВСЕХ!!!
		//назначаем адрес
		int b = bind(sock,(struct sockaddr*)&addr,sizeof(addr));
		if(b == -1)
		{
			fprintf(stderr,"ERROR: bind() \n");
			exit(1);
		}
		//запускаем потоковую фукцию
		if(pthread_create(&thread,NULL,&func_thread,NULL) != 0)    //&my_fifo
        	{
			fprintf(stderr,"ERROR: pthread_create() ! \n");
			exit(1);
        	}

		int broadcast =1;
		setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&broadcast,sizeof broadcast);

		while(1)
		{
			//printf("recv >\n");
			memset(&buf,0,sizeof(buf));
			int recv = recvfrom(sock,buf,sizeof(buf),0,NULL,NULL);
			if(recv == -1)
				fprintf(stderr,"ERROR: recvfrom() \n");
			printf("recv ->> %s\n",buf);
		}
	}	
return 0; 
}

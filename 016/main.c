#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int arg,char **argv)	//arg - кол-во аргументов
{				//argv - ук на аргумент
  
	if(arg != 2)   //
	{
		printf("error! number arg is NULL! \n");
		printf("format: ./%s my_port",argv[0]);
		exit(1);
	  }

	int my_port = atoi(argv[1]);
	
	struct sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
  
	int sock=socket(AF_INET, SOCK_STREAM, 0);
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = htonl((in_addr_t) INADDR_ANY);
	inaddr.sin_port = htons(my_port);

	if(bind(sock,(struct sockaddr*)&inaddr,sizeof(inaddr))<0)
	{
		printf("error: bind()");
		exit(1);
	}

	if(listen(sock, 5)<0)
	{
		printf("error: listen()");
		exit(1);
	}

	FILE* fd_htm = fopen("index.html", "r");
	fseek(fd_htm, 0, SEEK_END);
	long fd_size = ftell(fd_htm);

	char message[100];

while(1)
{
	//запрос на соединение
	int sock_accept = accept(sock,NULL,NULL);	//новый сокет для работы
	if(sock_accept < 0)
	{
		printf("error: accept()\n");
		break;
	}

	//ожидаем сообщение от клиента
	int bytes = recv(sock_accept,message,sizeof(message),0);
	if(bytes<=0)
	{
		printf("error: recv()\n");
		break;
	}
	//если bytes>0 - знаем размер данных
	message[bytes] = '\0';	//метка конца строки
printf("client --> \n %s \n",message);

	//формируем ответ
/*
HTTP/1.1 200 OK\n
Connection: keep-alive\n
Content-Type: text/html; charset=UTF-8\n
Keep-Alive: timeout=5,max=97\n
\n\n
*/

char uploadBuff[1024];
strcpy(uploadBuff,"GET / HTTP/1.1 200 OK\r\n");
strcat(uploadBuff,"Host index,html\r\n");
//strcat(uploadBuff,"Version: HTTP/1.1\r\n");
//strcat(uploadBuff,"Host: index.html\r\n");
//strcat(uploadBuff,"Content-Type: text/html; charset=UTF-8");
strcat(uploadBuff,"\r\n\r\n");

//strcat(uploadBuff,"Connection: keep-alive\n");
//strcat(uploadBuff,"Content-Type: text/html; charset=UTF-8\n");
//strcat(uploadBuff,"Keep-Alive: timeout=5,max=97\n\n");
//strcat(uploadBuff,"Error 404 page not found\n\n");

//strcpy(uploadBuff,"<head><title>Index</title></head><body><div>my text</div></body></html>\n\n");

printf("- answer: -\n %s",uploadBuff);

int ii = send(sock_accept,uploadBuff,sizeof(uploadBuff),0);
printf("ii = %d \n",ii);

close(sock_accept);
}

return 0; 
}

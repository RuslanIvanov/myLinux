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

int main(int arg,char **argv)
{			  
	if(arg != 2)
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

	if(listen(sock, 1)<0)
	{
		printf("error: listen()");
		exit(1);
	}

	FILE* fd_htm = fopen("index.html", "r");
	fseek(fd_htm, 0, SEEK_END);
	long fd_size = ftell(fd_htm);

	char message[100];


    sockaddr_in fromaddr;
    socklen_t ln=sizeof(fromaddr);

	char uploadBuff[1024];

while(1)
{
	//запрос на соединение
	int sock_accept = accept(sock,(sockaddr*)(&fromaddr), &ln);	//новый сокет для работы
	if(sock_accept <= 0)
	{
		printf("error: accept() %d\n",sock_accept);
		break;
	}
	//ожидаем сообщение от клиента-размер данных
	int bytes = recv(sock_accept,message,sizeof(message),0);
	if(bytes<=0)
	{
		printf("error: recv()\n");
	break;
	}
	message[bytes] = '\0';	//метка конца строки

printf("from client -----> \n %s \n",message);
int code_ans = 0;

	char *html = strstr(message,"index.html");
	if (html == NULL)
		code_ans =404;

printf("code = %d \n",code_ans);
char head[1024];
char *tmp = head;
int len =0;

	if(code_ans==404)
	{

/*		tmp = stpcpy(tmp,"HTTP/1.1 404 Not Found\r\n");
		tmp = stpcpy(tmp,"Connection: keep-alive\r\n");
		tmp = stpcpy(tmp,"Content-Type: text/html; charset=UTF-8\r\n");
                tmp = stpcpy(tmp,"Keep-Alive: timeout=5,max=97\r\n");
                tmp = stpcpy(tmp,"\r\n\r\n");
                tmp = stpcpy(tmp,"Error 404 Page not found\r\n\r\n");
*/
		strcpy(uploadBuff,"HTTP/1.1 404 Not Found\r\n");
		strcat(uploadBuff,"Connection: keep-alive\r\n");
		strcat(uploadBuff,"Content-Type: text/html; charset=UTF-8\r\n");
		strcat(uploadBuff,"Keep-Alive: timeout=5,max=97\r\n");
		strcat(uploadBuff,"\r\n");
		strcat(uploadBuff,"Error 404 Page not found\r\n\r\n");

                len = strlen("HTTP/1.1 404 Not Found\r\n");
                len +=strlen("Connection: keep-alive\r\n");
                len +=strlen("Content-Type: text/html; charset=UTF-8\r\n");
                len +=strlen("Keep-Alive: timeout=5,max=97\r\n");
                len +=strlen("\r\n");
                len +=strlen("Error 404 Page not found\r\n\r\n");


	}
/*
strcpy(uploadBuff,"HTTP/1.1 200 OK\n");
strcat(uploadBuff,"Connection: keep-alive\n");
strcat(uploadBuff,"Content-Type: text/html; charset=UTF-8\n");
strcat(uploadBuff,"Keep-Alive: timeout=5,max=97\n\n");

strcat(uploadBuff,"<head><title>Index</title></head><body><div>my text</div></body></html>\n");

printf("\n\n- answer: -\n%s",uploadBuff);
*/

int send_ans = send(sock_accept,uploadBuff,len,0);
printf("send_ans = %d \n%s\n",send_ans,uploadBuff);

//close(sock_accept);
}

return 0; 
}

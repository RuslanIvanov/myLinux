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

//	FILE* fd_htm = fopen("index.html", "r");
//	fseek(fd_htm, 0, SEEK_END);
//	long fd_size = ftell(fd_htm);

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
	if(bytes < 0)
	{	//ошибка получения данных
		printf("error: recv() failed\n");
		close(sock_accept);
//	break;
	}
	else if(bytes == 0)
	{	//соединение закрыто клиентом
		printf("connection closed\n");		
	}
	else if(bytes > 0)
	{	//полученные данные
		message[bytes] = '\0';	//метка конца строки
		//формируем ответ
printf("from client -----> \n %s \n",message);
int code_ans = 0;

	char *html = strstr(message,"index.html");
	if (html == NULL)
		code_ans = 404;
	else code_ans = 200;

printf("code = %d \n",code_ans);
char head[1024];
char *tmp = head;
int len =0;

		if(code_ans == 200)
		{
			char buff[1024];

			FILE* fd_htm = fopen("index.html", "r");
			if(fd_htm == 0)
				printf("error open()");
			//размер файла
			fseek(fd_htm,0,SEEK_END);
			long int size_htm = ftell(fd_htm);
			//считываем данные из файла
			fseek(fd_htm, 0, SEEK_SET);
			int r = fread(tmp,size_htm,1,fd_htm);
printf("----->\ntmp = %s \n",tmp);
			//формируем ответ,считанный из файла
	                strcpy(uploadBuff,"HTTP/1.1 200 OK\r\n");
        	        strcat(uploadBuff,"Connection: keep-alive\r\n");
                	strcat(uploadBuff,"Content-Type: text/html; charset=UTF-8\r\n");
	                strcat(uploadBuff,"Keep-Alive: timeout=5,max=97\r\n");
        	        strcat(uploadBuff,"\r\n");
			strcat(uploadBuff,tmp);
			//рассчитываем размер сообщения
	                len = strlen("HTTP/1.1 200 OK\r\n");
        	        len +=strlen("Connection: keep-alive\r\n");
                	len +=strlen("Content-Type: text/html; charset=UTF-8\r\n");
	                len +=strlen("Keep-Alive: timeout=5,max=97\r\n");
        	        len +=strlen("\r\n");
			len +=size_htm;
printf("------\n\nbuff=%s \n",uploadBuff);
//printf("------\n\ntmp=%s \nsize=%ld \n",tmp,size_htm);
			fclose(fd_htm);
		}
        	else if(code_ans == 404)
        	{
			//ответ - страница не найдена
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
		int send_ans = send(sock_accept,uploadBuff,len,0);
//printf("send_ans = %d \n%s\n",send_ans,uploadBuff);
		sleep(1);
		close(sock_accept);
	}
	}

return 0; 
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//socket
#include <sys/socket.h>	//socket
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>	//close(socket)

using namespace std;

struct client_message
{
int id_client;
char *message;
};

//int num = 0;
//struct client_message msg[10];

int func_spisok(int name, char* msg)
{

int n = name;
char* str = msg;


//msg.id_client[num] = name;
//msg->message = "kjkhjhj";

//printf("message list - name=%d msg %s \n",n,str);

//printf("message list - name=%d msg %s \n",msg[num].id_client,msg[num].message);
//num++;
//if(num==10)
//num =0;

return 0;
}


int main(int arg,char **argv)
{
	int sock,sock_accept;

	if(arg != 2)
	{
		fprintf(stderr,"ERROR: number arg is NULL! \n");
		printf("./myserver port_name \n");
		exit(1);
  	}
  	else
  	{
        	char message[BUFSIZ];
		char message_serv[BUFSIZ];

		//создаем сокет
 		int sock = socket(AF_INET,SOCK_STREAM,0);
		if(sock == -1)
		{
			fprintf(stderr,"ERROR: create socket() \n");
			exit(1);
		}
        	
		struct sockaddr_in serv_addr;
		int my_port = atoi(argv[1]);		//port

		memset(&serv_addr, 0, sizeof(sockaddr_in));		

		//определяем параметры соединения c сервером
		serv_addr.sin_family = AF_INET;			//домены internet
		serv_addr.sin_port = htons(my_port);		//порт
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//все

		//связываемся с сетевым устрйством
		if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		{
			close(sock);
			exit(1);
		}
		
		listen(sock,5);		//очередь входных подключений

int name_client = 0;			//имя клиента (просто порядковый номер)
		
		while(1)
		{
			//запрос на соединение
			sock_accept = accept(sock,NULL,NULL);	//новый сокет для работы
			if(sock_accept < 0)
			{
				printf("accept () \n");
				//exit(1);
			}
			name_client++;		//ID client
			if(fork() == 0)
			{
				printf("+ Подключился клиент: ID_%d \n",name_client);

				while(1)
				{
//printf("            -> ожидаем сообщение от клиента: \n");
					int bytes = recv(sock_accept,message,sizeof(message),0);
					if(bytes<=0)
						break;
//msg[num].id_client = name_client;
// char all_message;
 //memset(&all_message,0,sizeof(all_message));
 //sprintf(all_message,"client ID_%d, message: %s",name_client,message);
//printf("\n\n ------------------> id_client = %d",msg[num].id_client);
//num++;
//if(num==10)
//	num =0;

printf("            -> client ID_%d. message: %s \n",name_client,message);
					if(strcmp(message,"exit") == 0)
                                                printf("- Отключился клиент: ID_%d \n",name_client);
//char *msg = message;
					func_spisok(name_client,message);
/*
 char all_message[BUFSIZ];
//memset(&all_message,0,sizeof(all_message));
sprintf(all_message,"client ID_%d, message: %s",name_client,message);
printf("\n\n ------------------> %s",all_message);
*/
					send(sock_accept,message,sizeof(message),0);
				
				}
				close(sock_accept);	//break
			}
			else
				close(sock_accept);
		}		
	}	
return 0; 
}

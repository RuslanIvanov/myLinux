#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>	//socket
#include <sys/socket.h>	//socket
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>	//close(socket)
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

//char* file_log = './logsrv.txt';

struct client_message
{
int id_client;
char *message;
};

//int num = 0;
//struct client_message msg[10];

int func_spisok(int name, char* msg,int bytes)
{
//функция записи сообщений в log
int n = name;
char* str = msg;
int b = bytes;

	FILE *fd;
	fd = fopen("./logsrv","a+");
	if(fd == 0)
		printf("error open()");
	//strcat(str,"\n");
	fputs(str,fd);
	fputs("\n",fd);
	fclose(fd);

//write(fd,"cxkvjcxkjvlcxv",bytes);
//msg.id_client[num] = name;
//msg->message = "kjkhjhj";

//////////printf("message list - name=%d msg %s \n",n,str);

//printf("message list - name=%d msg %s \n",msg[num].id_client,msg[num].message);
//num++;
//if(num==10)
//num =0;

return 0;
}

int func_spisok_to_client(int sock_accept)
{
char message_serv[10];

strcat(message_serv,"nn345");
send(sock_accept,message_serv,sizeof(message_serv),0);


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


//создаем файл куда складываем лог
mode_t fmode = S_IWUSR;
int file_msg = creat("./logsrv",0777);//fmode);
close (file_msg);


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
func_spisok(name_client,message,bytes);

printf("            -> client ID_%d. message: %s \n",name_client,message);

					if(strcmp(message,"exit") == 0)
                                        {
					        printf("- Отключился клиент: ID_%d \n",name_client);
						break;	// выходим, закрываем сокет
					}

					//ищем в сообщении запрос на печать последних N сообщений
					char *find_msgN;
					find_msgN = strstr(message,"msgN");
 
					if(find_msgN)	//если пришел запрос от кл
					{
						char buf[10];
						int num_msg = 0;
						strcpy(buf,&message[4]);
						num_msg = atoi(buf);
						//если есть запрос на N сообщений
						if(num_msg != 0)
						{
/*
         FILE *fd;
         fd = fopen("./logsrv","r");
         if(fd == 0)
                 printf("error open()");
//        fseek(fd, 0, SEEK_END); 
	//strcat(str,"\n");
char load_string[50] = "none";
for(int i=0;i<num_msg;i++)
{

fseek(fd, 0, SEEK_END-i);
char *est = fgets( load_string, 50 , fd );
if(est == NULL)
	break;
strcat(message_serv,load_string);
printf("i=%d msg = %s  \n",i,load_string);

}
         fclose(fd);

send(sock_accept,message_serv,sizeof(message_serv),0);


//func_spisok_to_client(sock_accept);
*/
						}

printf("buf = %s num = %d \n",buf,num_msg);
					}
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

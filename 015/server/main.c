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
#include <pthread.h>
#include <vector>

using namespace std;

//char* file_log = './logsrv.txt';
char message_serv[BUFSIZ];
int count_msg = 0;
//flag fl = false;
pthread_mutex_t mutex;

int func_spisok(int name, char* msg,int bytes)
{
	int n = name;
	char* str = msg;
        char c[5];
pthread_mutex_lock (&mutex);
	FILE *fd;
	fd = fopen("./logsrv","a+");
	if(fd == 0)
		printf("error open()");
	else
	{
		fputs("ID_",fd);
		sprintf(c,"%d ",n);
		fputs(c,fd);
		fputs(str,fd);
		fputs("\n",fd);
	        count_msg++;	 //считаем кол-во строк
	}
	fclose(fd);
pthread_mutex_unlock (&mutex);
return 0;
}

int func_spisok_to_client(int N)
{
pthread_mutex_lock (&mutex);

	int num_msg = N;
	char str[BUFSIZ];

        memset(message_serv,0,sizeof(message_serv));
	memset(str,0,sizeof(str));

        FILE *fd;
	fd = fopen("logsrv","r");
	//проверка открытия файла         
	if(fd == 0)
                 printf("error open()");
	else
	{
	if (fseek (fd,0,SEEK_SET)!=0)
		printf ("error fseek()\n");

	char *estr;
	int set = count_msg - num_msg;	//позиция для считывания

	for(int cur=0;cur<count_msg;cur++)
	{
                estr = fgets(str,sizeof(str),fd);
                if(estr == NULL)
                {
                        if(feof(fd) == 0)
                                printf("error: fgets()\n");
                        break;
                }     
                //printf("-------> %s ",str);
		if(cur >= set)
			strcat(message_serv,str);
	}

//	printf("Сообщение сформрованное сервером:\n%s \n",message_serv);
	if(fclose(fd) == EOF)
		printf("error fclose()\n");
	}
pthread_mutex_unlock(&mutex);
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

		//создаем файл куда складываем лог
		int file_msg = creat("./logsrv",0777);
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

		int name_client = 0;	//имя клиента (просто порядковый номер)
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
					//ожидаем сообщение от клиента
					int bytes = recv(sock_accept,message,sizeof(message),0);
					if(bytes<=0)
						break;
					//запись всех сообщений текущей сессии в log-файл
					func_spisok(name_client,message,bytes);
					printf("            -> client ID_%d. message: %s \n",name_client,message);

					//exit - отключение клиента
					if(strcmp(message,"exit") == 0)
                                        {
					        printf("- Отключился клиент: ID_%d \n",name_client);
						break;	// выходим, закрываем сокет
					}

					//печать последних N сообщений
					//формат сообщения от клиента msgN8 (8 посл сообщений)
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
						printf("count_msg = %d \n",count_msg);
						func_spisok_to_client(num_msg);
					//	send(sock_accept,message_serv,sizeof(message_serv),0);
						}
					}
					send(sock_accept,message_serv,sizeof(message_serv),0);
				}
				close(sock_accept);	//break
			}
			else
				close(sock_accept);
		}		
pthread_mutex_destroy(&mutex);	
	}	
return 0;
}

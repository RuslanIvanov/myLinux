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
#include <syslog.h>

#define HTML_text	200
#define HTML_image	201
#define HTML_error	404

bool start_dmn = false;

void sig_handler(int s)
{
	printf("bye...\n");
	if(start_dmn)
	{
		openlog("stat_server", 0, LOG_USER);
		syslog(LOG_NOTICE, "Daemont end working");
		closelog();
	}	
	if(raise(SIGTERM)==-1)
		printf("Error: SIGTERM \n");
}

int error_arg()
{
	printf("Error! options \n");
	printf("Options:\n");
	printf("        -pXXXX port number\n");
	printf("        -d daemon\n\n");
	printf("Usage:\n./static_server -pXXXX\n");
	printf("./static_server -pXXXX -d\n\n");
	exit (0);
}
	
int main(int arg,char *argv[])
{
	int  rez = 0;					//getopt()
	//bool start_dmn = false;
	int  my_port = 0;

	while((rez = getopt(arg,argv,"p:d"))!=-1){	//перебираем все опции пока не будет -1
		switch(rez){
			case 'p':
			        my_port = atoi(optarg);
				break;
			case 'd':
				start_dmn = true;
				break;
			default:
				error_arg();
		}
	}

	if(!arg || !my_port)
		error_arg();
	
	if(start_dmn == true)
	{
		pid_t pid = fork();     //создаем потомка
		if(pid == -1){  //если не удалось запустить потомка	
			printf("Error: start Daemon failed\n");
			exit (1);
		}
		else if (pid == 0){     //если это потомок
			setsid();       //создаем новый сеанс
			chdir("/");     //идем в корень
			//закрываем дескрипторы ввода/вывода/ошибок
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			//return stat_dmn;

			openlog("stat_server", 0, LOG_USER);
			syslog(LOG_NOTICE, "Daemont start working");
			closelog();
		}
	}

        struct sigaction sig_act;
        sigemptyset(&sig_act.sa_mask);          //обнуляем
        sig_act.sa_flags = 0;                   //набор флагов
        sig_act.sa_handler = sig_handler;       //функция-обработчик

        if(sigaction(SIGINT,&sig_act,NULL)==-1){
                printf("Error: sigaction() \n");
                return 1;
        }

	struct sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
  
	int sock=socket(AF_INET, SOCK_STREAM, 0);
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = htonl((in_addr_t) INADDR_ANY);
	inaddr.sin_port = htons(my_port);

	if(bind(sock,(struct sockaddr*)&inaddr,sizeof(inaddr))<0){
		printf("error: bind()");
		exit(1);
	}

	if(listen(sock, 5)<0){
		printf("error: listen()");
		exit(1);
	}

	char message[100];
	sockaddr_in fromaddr;
	socklen_t ln=sizeof(fromaddr);
	char uploadBuff[1024];

	while(1)
	{
		//запрос на соединение
		int sock_accept = accept(sock,(sockaddr*)(&fromaddr), &ln);
		if(sock_accept <= 0){
			printf("error: accept() %d\n",sock_accept);
			break;
			}
		//ожидаем сообщение от клиента-размер данных
		int bytes = recv(sock_accept,message,sizeof(message),0);
		if(bytes>0)
		{
			//полученные данные
			message[bytes] = '\0';	//метка конца строки
			//формируем ответ
			printf("запрос:\n%s\n",message);
			int code_ans = 0;

			if(strstr(message,"GET /index.html"))
				code_ans = HTML_text;
			else code_ans = HTML_error;
				//printf("code = %d \n",code_ans);
		
			char head[BUFSIZ];
			char *tmp = head;
			int len =0;
		
			if (code_ans == HTML_text){
				char buff[1024];
				FILE* fd_htm = fopen("index.html", "r");
				if(fd_htm == 0)
					printf("error: open()");
				//размер файла
				fseek(fd_htm,0,SEEK_END);
				long int size_htm = ftell(fd_htm);
				//считываем данные из файла
				fseek(fd_htm, 0, SEEK_SET);
				int r = fread(tmp,size_htm,1,fd_htm);
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
				fclose(fd_htm);
			}
        		else	{
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
			printf("\nответ:\n%s\n",uploadBuff);
			sleep(1);
			close(sock_accept);
		}
	}

return 0; 
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

sig_atomic_t sig_flag= 0;

void handler_usr1(int s)
{
    sig_flag = 1;
}

void *thread_reader_func(void*)		//
{

return 0;
}

void *thread_writer(void*)		//writer to thread
{

return 0;
}



int main(int arg,char **argv)	//arg - кол-во аргументов
{
    char *p;
    struct sigaction act_usr;

				//argv - ук на аргумент
    if(arg == 1)   //если пользователь ничего не ввел
    {
       printf("ERROR! number arg is NULL! \n");
       exit(1);
    }
  
    int max = atoi(argv[3]);
    int num_reader = atoi(argv[1]);
    int num_writer = atoi(argv[2]);

  
    p = new char [max];
    memset(p,0,sizeof(p));

    if(sigaction(SIGINT,&act_usr,NULL) == -1)
    {
        fprintf(stderr, "ERROR: sigaction() \n");
        return 1;
    }

    pthread_t* thread_reader = new pthread_t[num_reader];
    pthread_t* thread_writer = new pthread_t[num_writer];

   for(int i=0; i<num_reader;i++)
   {
//       pthread_t* thread_reader=new phtread_t;
       if (pthread_create(&thread_reader[i],NULL,&thread_reader_func,&p[1]))
       {
           printf("error thread_reader");
           return 1;
       }

   }

   for(int i=0; i<num_writer;i++)
   if (pthread_create(&thread_reader[i],NULL,&thread_reader_func,&p[1]))
   {
       printf("error thread_writer");
       return 1;
   }






for(int i=0;i<num_reader;i++)
    {
	if(pthread_join(thread_reader[i],NULL) != 0)
    	{
		fprintf(stderr,"ERROR: join() \n");
		perror("pthread_join");
		return 1;
	}
    }

for(int i=0;i<num_writer;i++)
    {
        if(pthread_join(thread_writer[i],NULL) != 0)
        {
                fprintf(stderr,"ERROR: join() \n");
                perror("pthread_join");
                return 1;
        }
    }





while(1)
{

        if(sig_flag == 1)
        { 
            fprintf(stderr,"\nGoodbye...\n");
            if (raise(SIGTERM) == -1)
                printf("ERROR: \n");
            sig_flag = 0;
        }

  
}







return (1); 
}


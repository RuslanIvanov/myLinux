#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

sig_atomic_t sig_flag = 0;
vector <int> my_vector;
pthread_mutex_t mutex;

void sig_handler(int snum)
{
	//fprintf(stderr,"signal.........................\n");
	sig_flag = 1;
}

void *thread_writer_func(void *max)
{
	//потоковые функции записывают 1 в vector
	int count = *(int*)max;
	while(!sig_flag)
	{
		pthread_mutex_lock (&mutex);
		long int size = my_vector.size();
		if(my_vector.size() < count)		//есть место для записи?
		{
			my_vector.insert(my_vector.end(),1);	//записываем 1 в конец вектора
//printf("-----> size = %ld %d %d\n",my_vector.size(),count,sig_flag);
		}
		pthread_mutex_unlock(&mutex);
	}		
return 0;
}

void *thread_reader_func(void *max)		//writer to thread
{
	//потоковые функции вычитывают 1 из вектора
	int count = *(int*)max;
	while(!sig_flag)
	{
		pthread_mutex_lock(&mutex);
		if(my_vector.size() > 0)	//удаляем элемент, если вектор не пуст
			my_vector.erase(my_vector.begin());	//удаляем из начала
		pthread_mutex_unlock(&mutex);	
	}
return 0;
}

int main(int arg,char **argv)	//arg - кол-во аргументов
{
	if(arg != 4)
	{
		printf("ERROR! number arg is NULL! \n");
		printf("./rwqueue  кол-во_писателей  кол-во_читалей  размер_вектора\n");
		exit(1);
	}
	else if(arg == 4)
	{	
    		struct sigaction act;
		sigemptyset(&act.sa_mask);
		act.sa_handler = &sig_handler;
		act.sa_flags = 0;

		if(sigaction(SIGINT,&act,NULL) == -1)
		{
			fprintf(stderr, "ERROR: sigaction() \n");
			return 1;
		}
 		
		int max = atoi(argv[3]);		// кол-во контейнеров
		int num_reader = atoi(argv[2]);		// кол-во читателей
		int num_writer = atoi(argv[1]); 	// кол-во писателей
		my_vector.reserve(max);			// резервируем емкость вектора

		//создаем потоки
		//читатели (затирают 1 из вектора)
		pthread_t* thread_reader = new pthread_t[num_reader];
		for(int i=0; i<num_reader;i++)
		{
			if (pthread_create(&thread_reader[i],NULL,&thread_reader_func,&max))
			{
				fprintf(stderr,"ERROR: pthread_create(thread_reader)");
				return 1;
			}
		}
		//писатели (записывают в конец вектора 1)
		pthread_t* thread_writer = new pthread_t[num_writer];
		for(int i=0; i<num_writer;i++)
		{
			if (pthread_create(&thread_writer[i],NULL,&thread_writer_func,&max))
			{
				fprintf(stderr,"ERROR: ptherad_create (thread_writer)");
				return 1;
			}
		}

	while(1)
	{
		if(sig_flag == 1)
		{             
			fprintf(stderr,"........bay...\n");
			break;	//далее синхронизиуемся и выходим
		}
		printf(" --> size my_vectror = % ld \n",my_vector.size());
		sleep(5);
	}

	for(int i=0;i<num_reader;i++)
       	{
                if(pthread_join(thread_reader[i],NULL) != 0)
        	{
                        fprintf(stderr,"ERROR: join thread_reader \n");
                	return 1;
                }
        }
	for(int i=0;i<num_writer;i++)
    	{
		if(pthread_join(thread_writer[i],NULL) != 0)
        	{
                	fprintf(stderr,"ERROR: join thread_writer \n");
	                return 1;
	        }
	}

	pthread_mutex_destroy(&mutex);
	delete [] thread_reader;
	delete [] thread_writer;
}

return 0; 
}

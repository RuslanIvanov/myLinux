#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <iostream>
#include <vector>
using namespace std;

#define SHM_ID 456500

int main(int arg, char** argv)
{
	//vector <int> *p_vector;
	int *share_size;
	int shmid;
	shmid = shmget((key_t)1234,sizeof(int),0777);
	if(shmid < 0)
	{
        	printf("Error: shmget()\n");
	        return 1;
    	}

	//p_vector=(vector<int> *)shmat(shmid, 0,SHM_RND);
	share_size = (int *)shmat(shmid,NULL,0);
	if(share_size == (void *)-1)
	{
		printf("Error: shmat()\n");
		return 1;
    	}

	//int size = share_size;
	//printf("size vector = %d \n",(int*)share_size);
	printf("size = %d \n", *share_size);
        	
    if(shmdt(share_size))
	printf("Error shmdt()\n");

    return 0;
}

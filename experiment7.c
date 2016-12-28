#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#define BUF1SIZ 50
#define TEXT_SZ 50
void producter(void);
void customer(void);
struct shared_use_st
{  
int written;//非0：表示可读，0表示可写
    char text[TEXT_SZ];//记录写入和读取的文本
}; 
union semun{  
int val;  
struct semid_ds *buf;  
unsigned short *arry;  
};


int main(int argc,char *argv[])
{
	pid_t pid;
	if ( (pid = fork()) < 0)
printf("fork error");

else if (pid == 0) {            /* child */
	
        //printf("child!\n");
	producter();
	exit(0);
        } 
	else{				/* parent */

	//printf("father!\n");
	customer();
	exit(0);
	}
	
}

int init_sem(int sem_id,int init_value)
{
	union semun sem_union;
	sem_union.val=init_value;
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)
	{
	printf("initsem fail!\n");
	return -1;
	}
	return 0;
}

int del_sem(int sem_id)
{
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
	{printf("delete sem fail!\n");
	return -1;}
}

int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=-1;
	sem_b.sem_flg=SEM_UNDO;
	
	if(semop(sem_id,&sem_b,1)==-1)
	{printf("P operation fail!\n");
	return -1;}
	return 0;
}

int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=1;
	sem_b.sem_flg=SEM_UNDO;
	
	if(semop(sem_id,&sem_b,1)==-1)
	{printf("v operation fail!\n");
	return -1;}
	return 0;
}


void producter(void)
{
	int sem_id;
	
	//int semop(intsemid, structsembuf *sops, unsigned nsops);
	//int semctl(intsemid, intsemnum, intcmd, ...);
	void *shm = NULL;
	//int run=1;
int running = 1; 
	struct shared_use_st *shared;
	int shmid;
	char buffer[BUF1SIZ + 1];
	sem_id=semget(ftok(".",'a'), 1,0666|IPC_CREAT);
	init_sem(sem_id,1);
	if(sem_id == -1)  
	    {  
		printf("semget failed\n");  
		return ; 
	    }  
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|	IPC_CREAT);  
	if(shmid == -1)  
	    {  
		printf("shmget failed\n");  
		return ; 
	    }  
	    //将共享内存连接到当前进程的地址空间
	shm = shmat(shmid, 0, 0);  
	if(shm == (void*)-1)  
	    {  
		printf("shmat failed\n");  
		return ;  
	    }  
	printf("\nMemory attached at %X\n", (int)shm);  

	shared = (struct shared_use_st*)shm;  
	shared->written = 0;
		
		while(running)//向共享内存中写数据
		 {  
			
	//数据还没有被读取，则等待数据被读取,不能向共享内存中写入文本
	if(shared->written == 1)  
	{  
	sleep(1);  
	printf("Waiting...\n");  
		  } else{
		sem_p(sem_id); 
		  //向共享内存中写入数据
		printf("Enter some text: ");  
		gets(buffer);  
		strcpy(shared->text, buffer);  
		//写完数据，设置written使共享内存段可读
		shared->written = 1;  
		sem_v(sem_id);
		//输入了end，退出循环（程序）
		if(strncmp(buffer, "end", 3) == 0)  
		{ running = 0; 
		
			
		   }
		}  
		}
		del_sem(sem_id);
		    //把共享内存从当前进程中分离
		if(shmdt(shm) == -1)  
		    {  
			printf("shmdt failed\n");  
			return ;  
			  }  
		sleep(2);

}

void customer(void)
{	void *shm = NULL;
	int running = 1;
	int sem_id;
	sem_id=semget(ftok(".",'a'), 1,0666|IPC_CREAT);
	if(sem_id == -1)  
	    {  
		printf("semget failed\n");  
		return ; 
	    }  
	int shmid;
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|	IPC_CREAT);
	if(shmid == -1)  
	    {  
		printf("shmget failed\n");  
		return ; 
	    }  
	struct shared_use_st *shared;
	shm = shmat(shmid, 0, 0);  
	if(shm == (void*)-1)  
	    {  
		printf("shmat failed\n");  
		return ;  
	    }  
	shared = (struct shared_use_st*)shm;  
	shared->written = 0;
	printf("\nMemory attached at %X\n", (int)shm); 
	
	while(running)
	{
	
	if(shared->written != 0)  
{  if(strncmp(shared->text, "end", 3) == 0)  
                {running = 0; break;} 
		sem_p(sem_id);
		
printf("You wrote: %s\n", shared->text);  
		
sleep(rand() % 3);  
            //读取完数据，设置written使共享内存段可写
shared->written = 0;  
            //输入了end，退出循环（程序）
	sem_v(sem_id);  

        }  
        else//有其他进程在写数据，不能读取数据
            {sleep(1);
		}  
        }  
	//把共享内存从当前进程中分离
		if(shmdt(shm) == -1)  
		    {  
			printf("shmdt failed\n");  
			return ;  
			  } 
	if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
printf("shmctl(IPC_RMID) failed\n");  
return;
    }  
	
	
}

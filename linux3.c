#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>

//extern_pid_t getpid()   无参数表示获取当前pid  失败返回-1  参数如果为pid 则返回进程组号，参数为0返回当前进程组号，失败返回0  unistd.h
//extern_uid_t getuid()   真实用户号  返回当前进程的UID 失败返回-1 unistd.h
//extern_uid_t getgid()   真实用户组号  返回当前进程的GID 失败返回-1 unistd.h 
//void exit(int status)    stdilib.h    有特定的清理操作，包括fclose
//void  _exit (int  status )  unistd.h    终止进程的函数
//pid_t fork(void)   unistd.h 创建进程函数  出错返回-1 返回0则在子进程中，返回子进程ID则在父进程中。
//pid_t wait(int* statloc)  sys/wait.h  statloc：可用于存放子进程的终止状态 返回终止进程的PID，出错返回-1
//int execl(const char *pathname,  const char *arg0, .../*(char*)0*/)      unistd.h   用于在进程中执行另一个可执行文件  
//const char *arg0 为要执行程序的命令行参数 出错返回-1

char* getmode(mode_t st_mode);
void copy(char source[]);
int main(int argc,char*argv[])
{
	char buf[100];
	int h;
	DIR* currentdir;
	struct dirent* currentdp;
	static char str_time[100];
	if(argc!=2)
	{
		printf("请输入正确的路径啊，小宝贝～～～\n");
		return 0;
	}
	if(getcwd(buf,100)==NULL)
		return 0;
	h=strlen(argv[1]);
	if(argv[1][h-1]!='/')
		{
			++h;
			argv[1][h-1]='/';
			argv[1][h]=0;
		}
	if((currentdir=opendir(argv[1]))==NULL)
		{printf("open diretory fail\n");return 0;}
	while((currentdp=readdir(currentdir))!=NULL)
	{
		char a[100];
		char source[500];
		memset(a,'\0',100);
		struct stat buffer;
		strcpy(a,argv[1]);
		strcat(a,currentdp->d_name);
		strcpy(source,a);
		copy(source);
		if(lstat(a,&buffer)<0)
			{
				printf("get stat error\n");
				return 1;
			}

		printf("%10s",getmode(buffer.st_mode));
		printf("%3d",buffer.st_nlink);
		printf("%8s",getpwuid(buffer.st_uid)->pw_name);
		printf("%8s",getgrgid(buffer.st_gid)->gr_name);
		printf("%6d",buffer.st_size);
		printf("%25s",currentdp->d_name);
		strftime(str_time, sizeof(str_time), "%Y%m%d,%H:%M",localtime(&(buffer.st_mtime))); 
		printf("%20s\n",str_time);
	}
	closedir(currentdir);
	return 0;
}

char* getmode(mode_t mode)
{
	char buf[10];
	memset(buf,'-',10);
	if(S_ISREG(mode))
		buf[0]='-';
	else if(S_ISDIR(mode))
		buf[0]='d';
	else if(S_ISDIR(mode))
		buf[0]='c';
	else if(S_ISDIR(mode))
		buf[0]='b';
	else if(S_ISDIR(mode))
		buf[0]='p';
	else if(S_ISDIR(mode))
		buf[0]='l';
	else if(S_ISDIR(mode))
		buf[0]='s';
	if(mode&S_ISUID)
		buf[1]='r';
	if(mode&S_IWUSR)
		buf[2]='w';
	if(mode&S_IXUSR)
		buf[3]='x';
	if(mode&S_IRGRP)
		buf[4]='r';
	if(mode&S_IWGRP)
		buf[5]='w';
	if(mode&S_IXGRP)
		buf[6]='x';
	if(mode&S_IROTH)
		buf[7]='r';
	if(mode&S_IROTH)
		buf[8]='w';
	if(mode&S_IWOTH)
		buf[9]='x';
	return buf;
}

void copy(char source[])
{
	pid_t pid;
	pid=fork();
	if(pid<0){printf("创建子进程错误！\n");}
	if(pid==0)
	{
		if(execl("/home/liliang/linux2.out", "./linux2.out",source, "/home/liliang/c", (char *)0)<0)
			printf("调用子程序错误！\n");
		
	}
	while(wait(NULL)!=pid)
	{}
	return;
}


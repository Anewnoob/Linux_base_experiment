#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
//char*getcwd(char*buf,size_t size);  //获取当前工作绝对路径   unistd.h
//DIR*opendir(const char*name);   //  open dir   dirent.h
//int closedir(DIR* dir);          //close dir
//struct dirent* readdir(DIR* dir);  //read dir  sys/types.h；dirent.h
//int lstat(const char* path,struct stat* buf); //read attribute    sys/stat.h
char* getmode(mode_t st_mode);    //get  mode

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
		memset(a,'\0',100);
		struct stat buffer;
		strcpy(a,argv[1]);
		strcat(a,currentdp->d_name);
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




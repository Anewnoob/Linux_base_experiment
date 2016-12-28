#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


char *getMode(mode_t mode, char *buff);


int main(int argc,char *argv[])
{	
	int h;
        DIR *currentdir;
	char buffer[9],tmp[50];
	struct dirent *currentdp;
	static char str_time[100];
	if(argc!=2)
	{printf("请输入正确的路径！！！\n");
	return 0;}

	h=strlen(argv[1]);
	if(argv[1][h-1]!='/')	
	{
	argv[1][h++]='/';
	argv[1][h]=0;} 
	if((currentdir=opendir(argv[1]))==NULL){
	printf("open file fail.\n");
	return 0;
	}
	else
	{printf("    Type  links  id  ");
	printf(" Size           name ");
	printf(" 		        time\n");
	while((currentdp=readdir(currentdir))!=NULL)
	{struct stat buff;
	strcpy(tmp,argv[1]);
	strcat(tmp,currentdp->d_name);
	if(lstat(tmp,&buff)<0)
	 {
	printf("lstat error");
	return 1;
	 }
	printf("%10s",getMode(buff.st_mode,buffer));
	printf("%3d",buff.st_nlink);
	printf("%7d",buff.st_uid);
	printf("%6d",buff.st_size);
	printf("%25s ",currentdp->d_name);
	strftime(str_time, sizeof(str_time), "%Y%m%d,%H:%M",localtime(&(buff.st_mtime))); 
	printf("%20s\n",str_time);
	
	
	}}
	return 0;
}

char *getMode(mode_t mode, char *buff){  
if (buff == NULL) {  
printf("buff can't be NULL\n");  
return NULL;  
     }  

memset(buff, '-', 9);  

if (mode & S_IRUSR)  
buff[0] = 'r';  
if (mode & S_IWUSR)  
buff[1] = 'w';  
if (mode & S_IXUSR)  
buff[2] = 'x';  
if (mode & S_IRGRP)  
buff[3] = 'r';  
if (mode & S_IWGRP)  
buff[4] = 'w';  
if (mode & S_IXGRP)  
buff[5] = 'x';  
if (mode & S_IROTH)  
buff[6] = 'r';  
if (mode & S_IWOTH)  
buff[7] = 'w';  
if (mode & S_IXOTH)  
buff[8] = 'x';  

buff[9] = NULL;  
return buff;  
}  

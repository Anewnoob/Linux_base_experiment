#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

char *getMode(mode_t mode, char *buf);
    

 int main(int argc,char *argv[])
{	
	int h;
	pid_t pid;
	char tmp[50];
        DIR *currentdir;
	char buffer[9];
	struct dirent *currentdp;
	static char str_time[100];
	
	if(argc!=2)
	{printf("please input right path!\n");
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
	{struct stat buf;
	strcpy(tmp,argv[1]);
	strcat(tmp,currentdp->d_name);
	if(lstat(tmp,&buf)<0)
	 {
	  printf("lstat error");
	  return 1;
	 }
	printf("%10s",getMode(buf.st_mode,buffer));
        if(S_ISDIR(buf.st_mode)&&strcmp(currentdp->d_name, ".") != 0 && strcmp(currentdp->d_name, "..") != 0){
   
	int g=strlen(tmp);
	if(tmp[g-1]!='/')	
	{
	tmp[g++]='/';
	tmp[g]=0;}  
	Copy(pid,tmp);

	}
	printf("%3d",buf.st_nlink);
	printf("%7d",buf.st_uid);
	printf("%6d",buf.st_size);
	printf("%25s",currentdp->d_name);
 	strftime(str_time, sizeof(str_time), "%Y%m%d,%H:%M",localtime(&(buf.st_mtime)));  
        printf("%20s\n",str_time);
	
	
	}}
	return 0;
}

char *getMode(mode_t mode, char *buf){  
   if (buf == NULL) {  
        printf("buf can't be NULL\n");  
       return NULL;  
     }  
 
    memset(buf, '-', 9);  
  
   if (mode & S_IRUSR)  
       buf[0] = 'r';  
   if (mode & S_IWUSR)  
        buf[1] = 'w';  
   if (mode & S_IXUSR)  
        buf[2] = 'x';  
   if (mode & S_IRGRP)  
        buf[3] = 'r';  
   if (mode & S_IWGRP)  
       buf[4] = 'w';  
   if (mode & S_IXGRP)  
        buf[5] = 'x';  
   if (mode & S_IROTH)  
        buf[6] = 'r';  
   if (mode & S_IWOTH)  
        buf[7] = 'w';  
   if (mode & S_IXOTH)  
       buf[8] = 'x';  
 
   buf[9] = NULL;  
   return buf;  
}  

void Copy(pid_t pid,char tmp[])
{	
	if ( (pid = fork()) < 0)
                printf("fork error");
        else if (pid == 0) {             
            	execl("/home/liliang/2.out","2.out",tmp,"/home/liliang/a",(char *)0);  //在子进程中～

        } else
        
        {int status;
	pid_t tmpPid = wait(&status);           /* parent父进程通过 wait 函数知道子进程已经结束 */     
        if (tmpPid == pid)
        {
       
        }                              
       	}	
        return ;


}




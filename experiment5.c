#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>



char *getMode(mode_t mode, char *buf);

typedef struct Group{
char argv1[50];
char argv2[50];
int argc;
}gro;
void *thr1(void *group)
{
sleep(2);
gro *p;
p=(gro *)group;	
ls_l(p->argv1);

return ((void *)0);

}

void *thr2(void *group)
{
sleep(2);
gro *p;
p=(gro *)group;	
cd_r(p->argv1,p->argv2);
return ((void *)0);

}
int main(int argc,char *argv[])
{
	
	int err;
	pthread_t tid;
	char  tmp[50],tmp1[50];
	gro *group;
	if(argc!=2)
	{printf("请输入正确的路径！！！\n");
	return 0;}
	group=(gro *)malloc(sizeof(gro));
	strcpy(tmp,argv[1]);
	strcpy(group->argv1,tmp);
	//strcpy(tmp1,argv[2]);
	//strcpy(group->argv2,tmp1);
	group->argc=argc;
	//printf("%s,%s,%d",group->argv1,group->argv2,group->argc);
	err=pthread_create(&tid,NULL,(void *)thr1,(void *)group);
	if(err!=0)
	{printf("Create pthreaf fail!\n");
	return 0;}
	
	pthread_exit(NULL);
	printf("main thread has exited!\n"); 
	exit(0);

}	



int ls_l(char argv1[])
{	
	
	int h;
	pid_t pid;
        DIR *currentdir;
	char buffer[9],tmp[50],tmp1[50];
	struct dirent *currentdp;
	static char str_time[100];
	

	h=strlen(argv1);
	if(argv1[h-1]!='/')	
	{
	argv1[h++]='/';
	argv1[h]=0;}
	//printf("%s",argv1); 
if((currentdir=opendir(argv1))==NULL){
	printf("open file fail.\n");
	return 0;
	}
	else
	{printf("    Type  links  id  ");
	printf(" Size           name ");
	printf(" 		        time\n");
	while((currentdp=readdir(currentdir))!=NULL)
	{struct stat buf;
	strcpy(tmp,argv1);
	strcat(tmp,currentdp->d_name);
	//printf("%s\n",tmp);
	if(lstat(tmp,&buf)<0)
	 {
	printf("lstat error");
	return 1;
	 }
	printf("%10s",getMode(buf.st_mode,buffer));
        //if(S_IRUSR(buf.st_mode)){printf("r");}else{printf("-");}

	if(S_ISDIR(buf.st_mode)&&strcmp(currentdp->d_name, ".") != 0 &&strcmp(currentdp->d_name, "..") != 0){

	int h=strlen(argv1);
	strcpy(tmp1,argv1);
	if(tmp1[h-1]!='/')	
	{
	tmp1[h++]='/';
	tmp1[h]=0;}    
	strcat(tmp1,currentdp->d_name);	
	int g=strlen(tmp1);
	if(tmp1[g-1]!='/')	
	{
	tmp1[g++]='/';
	tmp1[g]=0;}  
	//printf("\n/*%s*/\n",tmp1);
	Copy(tmp1);
	
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
	
int cd_r(char argv1[],char argv2[])

{   
	int i=1;
	int j=0,k=0,l,h;
	struct stat buf;
	char *ptr;
	char fname[200],buffer[500];
	DIR *currentdir;
	FILE *fpto,*fpfrom;

	struct dirent *currentdp;

	/*if(argc!=3)
	{printf("please input right path!\n");
	return 0;}*/
	h=strlen(argv2);
	if(argv2[h-1]!='/')	
	{
	argv2[h++]='/';
	argv2[h]=0;}
	if(lstat(argv1,&buf)<0)
	 {
	return 0;}
	if (S_ISREG(buf.st_mode))
	{
	for(j=strlen(argv1);j>=0;j--)
	  {if(argv1[j]=='/'){
	for(k=j+1,l=0;k<=strlen(argv1);k++)
		{fname[l]=argv1[k];
		l++;}
		break;}}
	strcat(argv2,fname);
	if((fpto=fopen(argv2,"wb"))==NULL)
	{printf("create new file fail.\n");
	return 0;}
	if((fpfrom=fopen(argv1,"r"))==NULL)
	{printf("open file fail.\n");
	return 0;}
	while((fgets(buffer,50,fpfrom))!=NULL)
	if(fputs(buffer,fpto)==EOF){printf("copy fail\n");}
printf("Copy success!\n");	
return 0;}
	
	if (S_ISDIR(buf.st_mode))
	{
	
	if(isdir(argv1,argv2)!=1){printf("REEOR!!!\n");}
	printf("Copy success!\n");

	return 0;
	}

}


	
int isdir(char argv[],char argv2[])

{	int i=1,h,k,l,j;
	DIR *currentdir;
	struct stat buf;
	struct dirent *currentdp;
	char divname[500],temp[500],tmp[500];
	char fname[200],buffer[500];
	FILE *fpto,*fpfrom;
	int fd1,fd2;
	
	
	
	strcpy(tmp,argv2);
	
	h=strlen(argv);
	for(j=h-2;j>=0;j--)
	  {if(argv[j]=='/'){
	for(k=j+1,l=0;k<=strlen(argv);k++)
		{fname[l]=argv[k];
		l++;}
		break;}}
	strcat(tmp,fname);
	
	mkdir(tmp,0777);

	h=strlen(tmp);
	if(tmp[h-1]!='/')	
	{
	tmp[h++]='/';
	tmp[h]=0;}    

	h=strlen(argv);
	if(argv[h-1]!='/')	
	{
	argv[h++]='/';
	argv[h]=0;}
	if((currentdir=opendir(argv))==NULL)
	  {printf("open fi le fail.");
	return 0;}
	else	
	  {while((currentdp=readdir(currentdir))!=NULL)
	   {

	strcpy(divname,argv);
	strcat(divname,currentdp->d_name);
	if(currentdp->d_type == DT_REG){
	strcpy(temp,tmp);
	strcat(temp,currentdp->d_name);
	//printf("%s\n",temp);
	if((fpto=fopen(temp,"wb"))==NULL)
	{printf("create new file fail.\n");
	return 0;}
	if((fpfrom=fopen(divname,"r"))==NULL)
	{printf("open file fail.\n");
	return 0;}
	while((fgets(buffer,50,fpfrom))!=NULL)
	if(fputs(buffer,fpto)==EOF){printf("copy fail\n");}
	fd1=open(temp,0644);
	fd2=open(divname, 0644);	
	dup2(fd2,fd1);
	//printf("%s\n",divname);
	
	
	}
	else if(currentdp->d_type == DT_DIR &&strcmp(currentdp->d_name, ".") != 0 &&strcmp(currentdp->d_name, "..") != 0){
	isdir(divname,tmp);}
	}}
	return 1;
}

void Copy(char tmp[])
{	

	int err;
	pthread_t tid;
	//char  tmp1[50];
	gro *group;
	group=(gro *)malloc(sizeof(gro));
	
	strcpy(group->argv1,tmp);
	
	strcpy(group->argv2,"/home/liliang/b");
	
	//printf("%s,%s,%d",group->argv1,group->argv2,group->argc);
	err=pthread_create(&tid,NULL,(void *)thr2,(void *)group);
	if(err!=0)
	{printf("Create pthreaf fail!\n");
	return ;
}


}

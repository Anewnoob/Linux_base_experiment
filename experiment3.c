#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[])

{   
	int i=1;
	int j=0,k=0,l,h;
	struct stat buf;
	char *ptr;
	char fname[200],buffer[500];
	DIR *currentdir;
	FILE *fpto,*fpfrom;

        struct dirent *currentdp;

	if(argc!=3)
	{printf("请输入正确的路径！！！\n");
	return 0;}
	h=strlen(argv[2]);
	if(argv[2][h-1]!='/')	
	{
	argv[2][h++]='/';
	argv[2][h]=0;}
 	  if(lstat(argv[i],&buf)<0)
	 {
	  return 0;}
         if (S_ISREG(buf.st_mode))
	{
	for(j=strlen(argv[i]);j>=0;j--)
	  {if(argv[i][j]=='/'){
	      for(k=j+1,l=0;k<=strlen(argv[i]);k++)
		{fname[l]=argv[i][k];
		 l++;}
		break;}}
	 strcat(argv[i+1],fname);
	if((fpto=fopen(argv[i+1],"wb"))==NULL)
	{printf("create new file fail.\n");
	  return 0;}
	if((fpfrom=fopen(argv[i],"r"))==NULL)
	{printf("open file fail.\n");
	  return 0;}
	while((fgets(buffer,50,fpfrom))!=NULL)
	if(fputs(buffer,fpto)==EOF){printf("copy fail\n");}
        printf("Copy success!\n");	
         return 0;}
 	
	if (S_ISDIR(buf.st_mode))
	{
 	
   	if(isdir(argv[1],argv[2])!=1){printf("REEOR!!!\n");}
	printf("Copy success!\n");
	return 0;
	}

}


 	
int isdir(char argv[],char argv2[])

{	int i=1,h,k,l,j;
	DIR *currentdir;
	struct stat buf;
	struct dirent *currentdp;
	char divname[500],aaa[500],bbb[500];
	char fname[200],buffer[500];
	FILE *fpto,*fpfrom;
	int fd1,fd2;
	
	
   	
	strcpy(bbb,argv2);
	
	h=strlen(argv);
	 for(j=h-2;j>=0;j--)
	  {if(argv[j]=='/'){
	      for(k=j+1,l=0;k<=strlen(argv);k++)
		{fname[l]=argv[k];
		 l++;}
		break;}}
	strcat(bbb,fname);
	
	mkdir(bbb,0777);

	h=strlen(bbb);
	if(bbb[h-1]!='/')	
	{
	bbb[h++]='/';
	bbb[h]=0;}    

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
	strcpy(aaa,bbb);
	strcat(aaa,currentdp->d_name);
	printf("fpto:");
	printf("%s\n",aaa);
	if((fpto=fopen(aaa,"wb"))==NULL)
	{printf("create new file fail.\n");
	  return 0;}
	if((fpfrom=fopen(divname,"r"))==NULL)
	{printf("open file fail.\n");
	  return 0;}
	while((fgets(buffer,50,fpfrom))!=NULL)
	if(fputs(buffer,fpto)==EOF){printf("copy fail\n");}
	fd1=open(aaa,0644);
	fd2=open(divname, 0644);	
	dup2(fd2,fd1);
	printf("fpfrom:");
	printf("%s\n",divname);
	
	
	}
	 else if(currentdp->d_type == DT_DIR &&strcmp(currentdp->d_name, ".") != 0 && strcmp(currentdp->d_name, "..") != 0){
	isdir(divname,bbb);}
	}}
	return 1;
}

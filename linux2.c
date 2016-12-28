#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

//FILE*fopen(const char*restrict pathname,const char*restrict type);

int main(int argc,char* argv[])
{
	int h;
	char buf[50];
	FILE* fpfrom;
	FILE* fpto;
	struct stat buff;
	memset(buf,'\0',50);
	if(argc!=3)
	{
		printf("你输入的路径的方式不对哟～小宝贝！\n");
		return 0;
	}
	h=strlen(argv[2]);
	if(argv[2][h-1]!='/')
	{
		++h;
		argv[2][h-1]='/';
		argv[2][h]=0;
	}
	if(lstat(argv[1],&buff)<0)
	{
		printf("get stat error\n");
		return 0;
	}
	if(S_ISREG(buff.st_mode))
	{
		char a[20];
		int i,j,k=0;
		i=strlen(argv[1]);
		for(;argv[1][i]!='/';i--){}
		for(j=i+1;j<=strlen(argv[1]);j++)
			{
				a[k]=argv[1][j];
				k++;
			}
		strcat(argv[2],a);
		if((fpto=fopen(argv[2],"wb+"))==NULL)
		{
			printf("creat file fail!!!\n");
			return 0;
		}
		if((fpfrom=fopen(argv[1],"r"))==NULL)
		{
			printf("open file fail!!!\n");
			return 0;
		}
		while(fgets(buf,50,fpfrom)!=NULL)
		{
			if(fputs(buf,fpto)==EOF){printf("copy fail！！！\n");return 0;}
			
		}
		printf("copy file succeed!!!\n");
	}
	else if(S_ISDIR(buff.st_mode))
	{
		if(isdir(argv[1],argv[2])!=1)
			{
				printf("copy dir fail!\n");
			}
		else printf("copy dir succeed!\n");
	}
	return 0;
}

int isdir(char argv[],char argv1[])
{
	DIR* currentdir;
	struct dirent* currentdp;
	int h,i,j=0,k;
	char a[500],b[500],c[500],d[500];
	char e[50];
	FILE* fpfrom;
	FILE* fpto;
	memset(a,'\0',500);
	memset(b,'\0',500);
	h=strlen(argv);
	for(;argv[h]!='/';h--){}
	for(i=h+1;i<=strlen(argv);i++)
		{
			a[j]=argv[i];
			j++;
		}
	strcpy(b,argv1);
	strcat(b,a);
	mkdir(b,0777);
	k=strlen(b);
	if(b[k-1]!='/')
	{
		++k;
		b[k-1]='/';
		b[k]=0;
	}
	k=strlen(argv);
	if(argv[k-1]!='/')
	{
		++k;
		argv[k-1]='/';
		argv[k]=0;
	}
	//printf("创建：");
	//printf("%s\n",b);
		
	if((currentdir=opendir(argv))==NULL)
		{printf("open dir fail！\n");return 0;}
	while((currentdp=readdir(currentdir))!=NULL)
		{
			memset(c,'\0',500);
			memset(d,'\0',500);
			memset(e,'\0',50);
			if(currentdp->d_type == DT_REG)
				{
					strcpy(c,argv);
					strcat(c,currentdp->d_name);
					strcpy(d,b);
					strcat(d,currentdp->d_name);
					//printf("fpfrom:");
					//printf("%s\n",c);
					//printf("fpto:");
					//printf("%s\n",d);
					if((fpfrom=fopen(c,"r"))==NULL)
					{
						printf("open file fail!!!\n");
						return 0;
					}
					if((fpto=fopen(d,"wb+"))==NULL)
					{
						printf("creat file fail!!!\n");
						return 0;
					}
					while(fgets(e,50,fpfrom)!=NULL)
					{
						if(fputs(e,fpto)==EOF){printf("copy fail！！！\n");return 0;}	
					}

				}
			else if(currentdp->d_type == DT_DIR &&strcmp(currentdp->d_name, ".") != 0 && strcmp(currentdp->d_name, "..") != 0)
				{
					strcpy(c,argv);
					strcat(c,currentdp->d_name);
					isdir(c,b);
				}
		}
	return 1;
}


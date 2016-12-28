#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct student
{
	int age;
        char name[20];
}element;

typedef struct node
{
	element data;
	struct node *next;
} listnode,*listptr;

listptr listcreate()
{
	listptr p;
	p=(listptr)malloc(sizeof(listnode));

	return p;
}

void listshow(listptr p)
{       


         while(p->next)
	{
	printf("%d   ",p->data.age);
        puts(p->data.name);
	p=p->next;
	 }
	printf("\n");
}  

listptr listinsert(listptr p,int da,char name[20])
{
        listptr q;
	q=(listptr)malloc(sizeof(listnode));

        q->data.age=da;
        strcpy(q->data.name,name);
        q->next=p;

        return q;
}
	
int main(int argc,char* argv[])
{       
	int i,data;
	char name[20];
        listptr q=NULL;
	for(;;){
        printf("-----------Input 0 to Create------------\n");
	printf("-----------Input 1 to Insert------------\n");
	printf("-----------Input 2 to show--------------\n");
	printf("-----------Input 3 to quit---------------\n");
        scanf("%d",&i);
        switch(i) {
	case 0:{q=listcreate();
	printf("Create List success!\n");
	break;}

        case 1:{
        if(q==NULL){
	printf("Please Create a list first.\n");
	break;}
        printf("Input an age to insert to the top of the list.\n");
         scanf("%d",&data);
	printf("Input a name to insert to the top of the list.\n");
         scanf("%s",name);
	q=listinsert(q,data,name); 
	break;}

        case 2:{
	if(q==NULL){
	printf("Please Create a list first.\n");
	break;}
	printf("----------------\n");
	printf("List show :\n");
	listshow(q);
	printf("----------------\n");
	break;}

        case 3:{return 0;}

        default: return 0;}
        }
};

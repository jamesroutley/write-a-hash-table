//Made by- Subhadeep Saha
//program in c
#include<stdio.h>
#include<stdlib.h>
//code for chain hashing
struct node
{
    int info;
    struct node *link;
};

struct node *start[10];

void inserter(int value, int key)
{

    key=key%10;

    struct node* ptr;
    struct node* newn=(struct node*)malloc(sizeof(struct node));
    newn->info=value;
    if(start[key]==NULL)
    {
        start[key]=newn;
        newn->link=NULL;
    }
    else
    {
        ptr=start[key];
        start[key]=newn;
        newn->link=ptr;
    }

}

void display()
{
    int i=0;
    struct node* ptr;
    //int d=0;
    while(i!=10)
    {
        ptr=start[i];
        printf("\nKey %d : ", i);

        if(ptr==NULL)
            printf("No value at this key");
        while(ptr!=NULL)
        {
            printf("%d\t",ptr->info);
            ptr=ptr->link;
        }

        i++;
    }
}
struct node *searchvalue(int item, int key)
{
    struct node* ptr;
    key=key%10;
    ptr=start[key];
    if(ptr==NULL)
    {
        return ptr;
    }
    while(ptr!=NULL)
    {
        if(ptr->info==item)
            return ptr;
        ptr=ptr->link;
    }
    return ptr;
}

void deletevalue(int item, int key)
{
    key=key%10;
    if(start[key]->info==item)
    {
        start[key]=start[key]->link;
        return;
    }
    struct node* ptr=start[key];
    struct node* ptr2=ptr;
    //ptr=start[key];
    while(ptr->info!=item )
    {
        ptr2=ptr;
        ptr=ptr->link;
    }
    if(ptr->link==NULL)
    {
        ptr2->link=NULL;

    }
    if(ptr->link!=NULL)
    {
        ptr2->link=ptr->link;
    }
    free(ptr);
}

int main()
{
    struct node* sptr;
    int x=0, item, option, key;
    while(x!=10)
    {
        start[x]=NULL;
        x++;
    }
    do
    {
        printf("\n\n1.Create a Hash Table for separate chaining");
        printf("\n2.Searching an item from the Hash Table");
        printf("\n3.Delete an item from Hash Table");
        printf("\n4.Display the Hash Table");
        printf("\n5.Exit from the program");
        printf("\nEnter your choice : ");
        scanf("%d", &option);
        switch(option)
        {
        case 1:{
            printf("\nEnter -1 to terminate");
            printf("\nEnter the data item : ");
            scanf("%d",&item);
            printf("\nEnter the key value : ");
            scanf("%d",&key);
            while(item!=-1)
            {
                inserter(item,key);
                printf("\nEnter the data item : ");
                scanf("%d",&item);
                printf("\nEnter the key value : ");
                scanf("%d",&key);
            }
            printf("\nHash Table is created\n");
            break;}
        case 2:{
            printf("\nEnter the data item you want to search : ");
            scanf("%d",&item);
            printf("\nEnter the key value of the data : ");
            scanf("%d",&key);
            sptr=searchvalue(item,key);
            if(sptr==NULL)
                printf("\nItem %d with key value %d is not present",item,key);
            else
                printf("\nItem %d with key value %d is found at location %d",item,key,sptr);
            break;}
        case 3:{
            printf("\nEnter the data item you want to delete : ");
            scanf("%d",&item);
            printf("\nEnter the key value of the data : ");
            scanf("%d",&key);
            deletevalue(item,key);
            break;}
        case 4:{
            display();
            break;}
        }
    }while(option<=4);
    printf("\nYour input have terminated the program\n");
    return 0;
}


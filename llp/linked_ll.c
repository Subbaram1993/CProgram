//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//								//
//								//
//	Name	: Single Linked List				//
//	Author	: Subbaramaiah Chevuru				//
//	Mail	: ram.subaram@gmail.com				//
//								//
//								//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//==============================================================//
//			Revision Log				//
//==============================================================//
//								//
//	2022-11-14 -	Added the initial draft C program for	//
//			Single Linked List.			//
//								//
//==============================================================//

#include <stdio.h>
#include <stdlib.h>

//Declaring the struct variable
struct Node
{
  int data;
  struct Node *link;
}*head=NULL;

// Declaring Global Variables here
int ele;

//Creating the Linked List

void create()
{
  char ch= 'y';
  do
  {
    printf("ch : %c",ch);
    struct Node *p,*q;
    p = (struct Node*)malloc(sizeof(struct Node*));
    printf("\nEnter the Data : \n");
    scanf("%d", &p->data);
    p->link = NULL;
    if(head == NULL)
    {
      head = p;
    }
    else
    {
      q->link = p;
    }
    q=p;
    scanf("%c",&ch);
  }while(ch!= 'n');
}

//Displaying the Linked List

void display()
{
  struct Node *p=head;
  if(p == NULL)
  {
    printf("\nList is Empty \n");
    //return 0;
  }
  else
  {
    while(p!=NULL)
    {
      if(p->data > 0)
      {
        printf("\033[1m\033[31m%2d -->", p->data);
        //p = p->link;
      }
      p = p->link;
    }
  }
}

//Searching an Element in the Linked List.

int search(int n)
{
  struct Node *p=head;
  int pos =1;
  while(p!=NULL)
  {
    if(p->data == n)
    {
      return pos;
    }
    pos++;
    p=p->link;
  }
  return pos;
}

// Deleting an element in the Linked List
// entered by an user.

int delete()
{
  int pos1 =1;
  struct Node *p,*t;
  p=head;
  printf("\n Enter the Element in the List :\n");
  scanf("%d",&ele);
  if(p->data == ele && p!=NULL)
  {
    head = p->link;
    free(p);
  }
  while(p->data != ele && p!=NULL)
  {
     t = p;
     p = p->link;
     pos1++;
  }
  if(p==NULL)
    return 0;
  t->link = p->link;
  free(p);
  return pos1;
}

//Reversing the Linked List

void reverse()
{
  struct Node *p=head, *t=NULL,*s=NULL;
  while(p!=NULL)
  {
    s = p->link;
    p->link =t;
    t = p;
    p = s;
  }
  head =t;
}

// Main function starts here

int main()
{
  int n,l,l2;
  create();
  printf("\nCreation Complete........ Displaying\n");
  display();
  printf("\n");
  printf("\033[1m\033[36m Enter the element to be searched in the list\n");
  scanf("%d",&n);
  l=search(n);
  (l==0)?printf("\nThe element \033[1m\033[37m%d \033[1m\033[36m is not in the List\n",n):printf("\n The element \033[1m\033[37m%2d is at %d \033[1m\033[36m in the list\n",n,l);
  display();
  reverse();
  printf("\n");
  display();
  printf("\n\033[0;37m\n");
  return 0;
}

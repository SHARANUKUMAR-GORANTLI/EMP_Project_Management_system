//1. reading data objects from keyboard and forming doubly-linked list 
//#pragma startup app_init
//#pragma exit app_close

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dlist.h"
#include"admin_main.h"
Node_t *head = NULL;
Node_t *tail = NULL;
Node_t * createNode(admin_t val)		//to create the DLL node
{
   Node_t *node = (Node_t *)malloc(1*sizeof(Node_t)); // (Node_t *)calloc(1,sizeof(Node_t))
   memset(node,0,sizeof(Node_t));
   node->data = val;   //memcpy(&node->data, &val, sizeof(book_t)) //shallow copy
   node->prev = NULL;
   node->next = NULL;
   
   return node;
}
void insertNodeBack(admin_t val)		//to add node at tail of DLL
{
	Node_t* node = createNode(val);
	
	if( head == NULL )
	{
		head = tail = node;
		
	}
    else
	{
	   tail->next = node;
	   node->prev = tail;
	   tail = node;
	}
}
void destroy()						//to destory the DLL
{
	
	if( head == NULL )
	{
	    //printf("\n\n Customer List is Empty ....\n");
	}
    else
	{
	    do
		{
			deleteNodeFront();		//to delete node from front in DLL
        }while(head != NULL);
	}	
}

void deleteNodeFront()				//to delete node from front in DLL
{
   Node_t* node = head;
   if(head->next != NULL)
   {
      head->next->prev = NULL;
      head = head->next;
   }
   else
   {
   	  head = tail = NULL; 	  
   }
   node->next = NULL;
   free(node);  
}
void doTraversal(fn_t printAdmin)	//to display all the admin details 
{
	Node_t *node = head;
	
	if( node == NULL )
	{
	    printf("\n\n Customer List is Empty ....\n");
	}
    else
	{
	    do
		{
			//printDetails(node->data);
			printAdmin(&node->data);		//function pointer to printAdmin() in admin_main.c
			node = node->next;
        }while(node != NULL);
	}	
}		








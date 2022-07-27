#pragma once
#include"object_t.h"
typedef struct _Node_t
{
	struct _Node_t *prev;
	admin_t data;
	struct _Node_t *next;
}Node_t;
typedef void (*fn_t)(admin_t* addr);
extern Node_t *head ;
extern Node_t *tail ;

void insertNodeBack(admin_t);			//to add node at tail of DLL
Node_t * createNode(admin_t);			//to create the DLL node
void destroy();							//to destory the DLL
void deleteNodeFront();					//to delete node from front in DLL
void doTraversal(fn_t printAdmin);		//to display all the admin details 

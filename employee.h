#pragma once
#include<stddef.h>
#include"object_t.h"

typedef struct _nod_t
{
	struct _nod_t *prev;
	employee_t data;
	struct _nod_t *next;
}node_t;
extern node_t *headEmp ;
extern node_t *tailEmp ;

#define BONUS 10000
node_t* creatnode(employee_t);
void reademployeeinfo(employee_t *);				//to read employee detaisl
void insertnode(employee_t);						//to insert the employee details to DLL
void read_emp_from_file();							//to display all the employee details
void printemployeeinformation(employee_t);			//to print the employee details
void Delete();										//to delete all the employee details from file and DLL
//void clear_input_buffer();
void DeleteById(int);								//to delete employee detail using employee id
int  empAlocation(int proId,int empId,int empPer);	//to add allocated project details to employee details
void readById(int);									//to read employee details by employee id
void employee_login();								//employee login
void empDeallocation(int proId,int empId);			//to remove project details from employee details
void empOperations();								//to create ,delete and search employee details





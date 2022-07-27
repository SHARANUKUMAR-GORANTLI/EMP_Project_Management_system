#pragma once
#include"employee.h"
#include"object_t.h"

void db_add_obj_into_file(employee_t *);            //adding employee details to the file DB
void db_read_allobj_from_file();                    //to read all employee details from file DB
void db_read_oneobj_using_id(employee_t *,int);     //to display the employee details by employee id
void db_update_obj_using_id(employee_t);            //to edit/update the employee details
void db_delete_obj_using_id();                      //to delete employee details based on id from file 
//void db_delete_obj_in_file(employee_t*);            //to delete all the employee details from file

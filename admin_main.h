#pragma once
#include "object_t.h"
#include<stdio.h>
#include<string.h>
#include"admin_main.h"
#include <stdlib.h>
#include"dlist.h"
#include"myutil.h"
#include"project_main.h"
#include"employee.h"

void create_admin();                                    //to create new admin login 
void add_admin(admin_t* admin);                         //to add new admin details to the file
void delete_admin( int id);                             //deleting admin details from file by admin id
void edit_admin(admin_t* admin);                        //to edit the admin details in files
void adminreadbyid(admin_t* adminaddr, int id);         //to read admin details from file by admin id
void admin_readAll(admin_t* admin, int* countAddr);     //to read all admin details from file
void changePassword(admin_t* admin);                    //to change admin password
void editAdmin(admin_t* admin);                         //to close the project and deallocate the employees from the project
void login();                                           //admin login function
void printAdmin(admin_t* addr);                         //to print the admin details
void readAllAdmin();                                    //to print all the admin details
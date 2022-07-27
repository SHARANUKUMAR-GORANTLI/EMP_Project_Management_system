#pragma once
#include"object_t.h"
#include<stdio.h>
#include<string.h>

void create_project();                                          //to create project details
void add_project(project_t * projects);                         //to add project details to file
void delete_project( int id);                                   //to delete the project details from file using project id
void edit_project(project_t project);                           //to edit/update project details in file
void readbyid(project_t* projectaddr, int projectId);           //to get the project details from file using project id
void project_readAllfile(project_t* project, int* countAddr);   //to get the all projects details from file
void project_readAll(int show);                                 //to display project details,1- all project details ,0- active project details
void project_deleteById();                                      //to delete project from file using project id
void edit_projects();                                           //to edit/update project details from file
void deleteFile();                                              //deleting all the project details from file
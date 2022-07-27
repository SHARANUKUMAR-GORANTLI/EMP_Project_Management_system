#include "admin_main.h"
#include <stdlib.h>
#include<stdio.h>
#include"myutil.h"
#include"dlist.h"
#include"object_t.h"
#include"project_main.h"
#include"employee_db.h"
#include"employee.h"
#include<threads.h>
long noofresourcesrequired = 0,noofemployeesallocated = 0, noofemployeesnotallocated = 0;
long resourceCount = 0;
int resource[32];
void donoofresourcesrequired()                              //thread function to count no of resources required
{
    project_t *project = (project_t *)malloc(20*sizeof(project_t));
    int count = 0;
    project_readAllfile(project,&count);
    for(int I = 0; I < count; I++)
    {
        if(project[I].status == 1)
        {
            resourceCount++;
            resource[resourceCount-1] = project[I].numOfEmpRequired;
        }
    }
    free(project);
	for(int i=0;i<resourceCount;i++)    
	        {       
	        	noofresourcesrequired += resource[i]; 
	        } 
}
int donoofresourcesrequired_routine()                       // thread rountine for donoofresourcesrequired()
{
	donoofresourcesrequired();
	return 0;
}
void docountallocate()                                      //thread function to calculate no of allocated and not alocated resources
{
     node_t * node = tailEmp;
            if(headEmp == NULL)
            {
               // printf("\n No employees \n");
                noofemployeesallocated = 0;
                noofemployeesnotallocated = 0;
            }
            else
            {
                while(node != NULL)
                {            
                    if(strcmp(node->data.emp_status,"Active")==0)
                    {
                       noofemployeesallocated++;
                    }
                    else
                    {
                        noofemployeesnotallocated++;
                    }
                    node = node->prev;
                }
            } 
	        
}
int docountallocate_routine()                           //thread rountine for docountallocate()
{
	docountallocate();
	return 0;
}
void process()                                          //to start the threading process
{
    noofresourcesrequired = 0;
    noofemployeesallocated = 0;
    noofemployeesnotallocated = 0;
    resourceCount = 0;
    memset(resource,0,sizeof(int)*32);
	thrd_t th1, th2; 
  //  user_t *users= (user_t *)malloc(20*sizeof(user_t));
    
    thrd_create(&th1,docountallocate_routine,NULL); 
    thrd_create(&th2,donoofresourcesrequired_routine,NULL);      
    thrd_join(th1,NULL);   
    thrd_join(th2,NULL);
    printf("\nCurrent Status");
    printf("\nno of resources required for all projects = %ld\tno of employees allocated = %ld\tno of employees not allocated =%ld\n",noofresourcesrequired,noofemployeesallocated, noofemployeesnotallocated);     
}
void create_admin()                                         //to create new admin login 
{
	system("clear");
    admin_t *admins=(admin_t *)malloc(sizeof(admin_t));
    memset(admins,0,sizeof(admin_t));
    
    printf("Enter admin Name:"); 
    scanf("%s",admins->adminname);
    printf("Enter admin id:"); 
    scanf("%d",&admins->id);
    clear_input_buffer(); 
	printf("Enter Password:"); 
    scanf("%s",admins->password);
    add_admin(admins);
    free(admins);
}
void add_admin(admin_t* admin)                          //to add new admin details to the file
{
	char fileName[] = "admin.dat";
	FILE* out = fopen(fileName, "ab");
	if(out == NULL)
	{
		printf("FILE ERROR. \n");
		return;
	}
	fwrite(admin, 1,sizeof(admin_t),out);
	fclose(out);
}
void delete_admin( int id)                          //deleting admin details from file by admin id
{
	int I=0;
    admin_t temp  = {};
    char fileName[] = "admin.dat";
    char tempFileName[] = "admintemp.dat";
    FILE* in = fopen(fileName,"r");
    FILE* out = fopen(tempFileName,"w");
    if(in == NULL){
        printf("(in)FILE ERROR.\n");
        return;
    }
    if(out == NULL){
        printf("(out)FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(admin_t),in)){
    	I++;
        if(temp.id != id){        	
        	fwrite(&temp,1,sizeof(admin_t),out);
        }        
    }    
    fclose(out);
    fclose(in); 
    remove(fileName);
    rename(tempFileName,fileName);
}
void edit_admin(admin_t* admin)             //to edit the admin details in files
{
	int I=0;
    admin_t temp = {};
    char fileName[] = "admin.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(admin_t),in)){
    	I++;
        if(temp.id == admin->id){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(admin_t),SEEK_SET);
    	fwrite(admin,1,sizeof(admin_t),in);
    }
    fclose(in);
}
void adminreadbyid(admin_t* adminaddr, int id)      //to read admin details from file by admin id
{
	int I=0;
    admin_t temp  = {};
    char fileName[] = "admin.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(admin_t),in)){
        if(temp.id == id){
        	(*adminaddr) = temp;
        	break;
        }
        I++;
    }
    fclose(in);

}
void admin_readAll(admin_t* admin, int* countAddr){             //to read all admin details from file
    int I=0;
    admin_t temp;
    
    char fileName[] = "admin.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(admin_t),in)){
        admin[I] = temp;
        I++;
    }
    fclose(in);
    (*countAddr) = I;
}
void changePassword(admin_t* admin)                         //to change admin password
{
    clear_input_buffer();                                   //to clear input buffer
	printf("Enter New Password:"); 
    scanf("%s",admin->password);
    edit_admin(admin);
    printf("\nPassword changed....\n"); 
}
void projectClose()                                        //to close the project and deallocate the employees from the project
{
    printf("\nAll active projects....\n"); 
    project_readAll(0);                                     // to show all the active projects
    int id;
    printf("\nEnter the Project Id to deallocate\n"); 
    scanf("%d",&id);
    project_t project;
    readbyid(&project, id);                                 //to get the project details from file using project id
    if(project.projectId == id)
    {
        project.status = 0;
        for(int i = 0;i<project.numOfEmpAllocated;i++ )    //fetching all the emp id for deallocation 
                    {
                       int empId;
                       empId = project.allocEmpId[i];       
                       empDeallocation(id,empId);           //to remove project from employee details
                    }
        edit_project(project);                              //update the project details

    }
    else
        printf("\nproject not found\n");
}
void projectAllocation()                                    //to allocate resoures to the project
{
    printf("\nAll active projects....\n"); 
    project_readAll(0);                                     //to show all active projects
    int id;
    printf("\nEnter the Project Id to Allocate\n"); 
    scanf("%d",&id);
    project_t project;
    readbyid(&project, id);                                 //to get the project details from file using project id
    if(project.projectId == id)
    {
        if(project.status == 1)
        {
            if((project.numOfEmpRequired > project.numOfEmpAllocated) && (project.allocatedper < 100))
            {
                read_emp_from_file();                                   //to show all the employee details from file
                printf("\nEnter the Emp Id to Allocate project\n"); 
                int empId,per;
                scanf("%d",&empId);
                printf("\nEnter the Emp  Allocation percentage to project\n"); 
                scanf("%d",&per);
                if((project.allocatedper + per)> 100)
                {
                    printf("\nCant allocate-Allocation Percentage for the project is more than 100  \n");
                    return;
                }
                int res = empAlocation(id,empId,per);                   //to updated the allocated project to the employee details
                if(res == 1)
                {
                    project.allocEmpId[project.numOfEmpAllocated] = empId;
                    project.allocEmpPer[project.numOfEmpAllocated] = per;
                    project.numOfEmpAllocated++;
                    project.allocatedper=0;
                    for(int i = 0;i<project.numOfEmpAllocated;i++ )
                    {
                        project.allocatedper += project.allocEmpPer[i];
                    }
                    edit_project(project);                               //update the project details
                }
                else
                    printf("\nAllocation Failed\n");

            }
            else
                printf("\nMax no of Employees is allocated or percentage of aloocation is 100 \n");
        }
        else
            printf("\nEmployee cant be added to closed project\n");
    }
    else
        printf("\nproject not found\n");
}
void login()                                                    //admin login function
{
    admin_t admin = {};
    int id=0;
    char password[32];
    system("clear");                                            //to clear the terminal window
    printf("Enter admin id:"); 
    scanf("%d",&id);  
    adminreadbyid(&admin,id);                                   //to get the admin details from file using admin id
    if(admin.id == id)
    {
       // system("clear");
        printf("\n\nWelcome %s (Admin)\n",admin.adminname);
        
        printf("Enter password\n");
        scanf("%s",password); 
        if(strcmp(password,admin.password)==0)
        {
            
             int menu;
            do{
                //system("clear");
                static int show = 0;
                if(show == 1)
                	process();                                  //to start the threading process
                // system("clear");
                printf("\n\nPick Choice\n");
                printf("\t1.create project\n");
                printf("\t2.delete project\n\t3.Read all project\n\t4.Edit project\n\t5.Employye operations\n\t6.Project Alocattion\n\t7.Close project\n\t8.Change password\n\t9.Delete Account\n\t0-Exit\n"); 
                printf("Your Choice:"); scanf("%d",&menu);
                
                printf("\n");
                if(1==menu){
                    system("clear");
                    create_project();                           //to create project
                    show = 1;                                   //to start the thread function after one time execution to admin operations(to avoid file error in project data base during thread process)
                }else if(2==menu){
                    system("clear");
                    project_deleteById();                       //to delete project by project id 
                }
                else if(3==menu){
                    //system("clear");
                    project_readAll(1);                         //to show all project details
                    clear_input_buffer();
                }
                else if(4==menu){
                     system("clear");
                    edit_projects();                            //to edit/update the project details
                }
                else if(5==menu){
                     system("clear");
                    empOperations();                            //to create ,delete ,search and display employee details
                }
                else if(6==menu){
                     system("clear");
                    projectAllocation();                        //to allocate resoures to the project
                }
                else if(7==menu){
                    system("clear");
                    projectClose();                             //to close the project and deallocate the employees from the project
                }
                else if(8==menu){
                    system("clear");
                    changePassword(&admin);                     //to change admin password
                    
                }
                else if(9==menu){
                    system("clear");
                    delete_admin(admin.id);                     //deleting admin details from file by admin id
                    return;
                }
                else if(0==menu){
                   system("clear");
                    printf("Shutting down the app....\n");
                }
                else{
                    printf("Invalid choose....\n");
                }
                //clear_input_buffer();
                //show = 1;                                       //to start the thread function after one time execution to admin operations(to avoid file error in project data base during thread process)
            }
            while(((1<=menu) && (menu<=8)));
            
        }
        else
            printf("\nInvalid Password");
    }
    else
        printf("\nInvalid Id");
}
void printAdmin(admin_t* addr)                                  //to print the admin details
{     
        printf("Admin id:%d\n",addr->id);
        printf("Admin name:%s\n",addr->adminname);   
}
void readAllAdmin()                                      //to print all the admin details
{
    system("clear");

    admin_t *admins= (admin_t *)malloc(20*sizeof(admin_t));
    memset(admins,0,sizeof(admin_t)*20);
    int count = 0;
    admin_readAll(admins,&count);                       //to get all the admin details from file
    if(count == 0)
    {
        printf("\nNo Admin data\n");
        return;
    }
    printf("\nAdmins\n");
    for(int I = 0; I < count; I++)
        insertNodeBack(admins[I]);                      //to add admin node to the double linklist 
    doTraversal(printAdmin);                            // to print the admin details using double linklist, here we are passing a function pointer to display the details
    free(admins);                                      
    destroy();                                          //to destroy the double linklist
}

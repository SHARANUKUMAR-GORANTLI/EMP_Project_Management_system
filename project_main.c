#define _XOPEN_SOURCE
#include<string.h>
#include"project_main.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void create_project()      //to create project details
{
	struct tm d1={}, d2={};
	time_t t1, t2;

	project_t *projects=(project_t *)malloc(sizeof(project_t));
	memset(projects,0,sizeof(project_t));

	printf("Enter Project Name:"); 
	scanf("%s",projects->projectName);
	
	static int Id = 1;
	projects->projectId = Id;
	printf("Project Id = %d \n", projects->projectId);
        Id++;
l1:
	printf("Enter Project start day [YYYY-MM-DD]:");
	scanf("%s",projects->start_date);

	printf("Enter Project end day:[YYYY-MM-DD]:");
	scanf("%s",projects->end_date);
	strptime(projects->start_date, "%Y-%m-%d", &d1);
	strptime(projects->end_date, "%Y-%m-%d", &d2);
	t1 = mktime(&d1);
	t2 = mktime(&d2);
	/* 30 day difference */
	if((t2-t1) < (2592000)) {
		printf("Invalid Date-min of 30 days required \n");
		goto l1;
	}

	printf("Enter No of emplyee required:"); 
	scanf("%d",&projects->numOfEmpRequired);
	projects->status = 1;
	add_project(projects);
    free(projects);
}
void add_project(project_t * projects)					//to add project details to file
{
	char fileName[] = "project.dat", buff[1024] = {0};
	FILE* out = fopen(fileName, "ab");
	if(out == NULL)
	{
		printf("FILE ERROR. \n");
		return;
	}
	fwrite(projects,1,sizeof(project_t),out);
	fclose(out);
}
void delete_project( int id)						//to delete the project details from file using project id
{
	int I=0;
    project_t temp;
    char fileName[] = "project.dat";
    char tempFileName[] = "temp.dat";
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
    while(fread(&temp,1,sizeof(project_t),in)){
    	I++;
        if(temp.projectId != id){        	
        	fwrite(&temp,1,sizeof(project_t),out);
        }        
    }    
    fclose(out);
    fclose(in); 
    remove(fileName);
    rename(tempFileName,fileName);
}
void edit_project(project_t project)			//to edit/update project details in file
{
	int I=0;
    project_t temp = {};
    char fileName[] = "project.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(project_t),in)){
    	I++;
        if(temp.projectId == project.projectId){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(project_t),SEEK_SET);
    	fwrite(&project,1,sizeof(project_t),in);
    }
    fclose(in);
}
void readbyid(project_t* projectaddr, int projectId)		//to get the project details from file using project id
{
	int I=0;
    project_t temp  = {};
    char fileName[] = "project.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&temp,1,sizeof(project_t),in)){
        if(temp.projectId == projectId){
        	(*projectaddr) = temp;
        	break;
        }
        I++;
    }
    fclose(in);

}

void project_readAllfile(project_t* project, int* countAddr){		//to get the all projects details from file
int I=0;
project_t temp = {};
char fileName[] = "project.dat";
FILE* in = fopen(fileName,"rb");
if(in == NULL){
    printf("FILE ERROR.\n");
    return;
}
while(fread(&temp,1,sizeof(project_t),in)){
    project[I] = temp;
    I++;
}
fclose(in);
(*countAddr) = I;
}

void project_readAll(int show)								//to display project details,1- all project details ,0- active project details
{
	
	project_t *projects = (project_t*)malloc(20*(sizeof(project_t)));
	int count = 0;
	project_readAllfile(projects,&count);
	if(count == 0)
	{
		printf("\nNo projects\n");
		return;
	}
	for(int I=0 ; I < count ; I++)
	{
		if(show == 1)
		{
			printf("\n\nProject Name:%s\n",projects[I].projectName);
			printf("Project ID:%d\n",projects[I].projectId);
			printf("Project Status:%d\n",projects[I].status);
			printf("No of emp required:%d\n",projects[I].numOfEmpRequired);
			printf("Project start date:%s\n",projects[I].start_date);
			printf("Project end date:%s\n",projects[I].end_date);
			printf("\tAllocated emp and percentage : \n");
			//projects[I].allocatedper=0;
			for(int i = 0;i<projects[I].numOfEmpAllocated;i++ )
			{
				printf("\tEmp ID : %d  Percentage : %d\n",projects[I].allocEmpId[i],projects[I].allocEmpPer[i]);
				//projects[I].allocatedper += projects[I].allocEmpPer[i];
			}
			printf("Total allocation :%d\n",projects[I].allocatedper);
			printf("******************************************");
		}
		else
		{
			if(projects[I].status == 1)
			{
				printf("\n\nProject Name:%s\n",projects[I].projectName);
				printf("Project ID:%d\n",projects[I].projectId);
				printf("Project Status:%d\n",projects[I].status);
				printf("No of emp required:%d\n",projects[I].numOfEmpRequired);
				printf("Project start date:%s\n",projects[I].start_date);
				printf("Project end date:%s\n",projects[I].end_date);
				printf("\tAllocated emp and percentage : \n");
				//projects[I].allocatedper=0;
				for(int i = 0;i<projects[I].numOfEmpAllocated;i++ )
				{
					printf("\tEmp ID : %d  Percentage : %d\n",projects[I].allocEmpId[i],projects[I].allocEmpPer[i]);
					//projects[I].allocatedper += projects[I].allocEmpPer[i];
				}
				printf("Total allocation :%d\n",projects[I].allocatedper);
				}
				printf("******************************************");
		}
        
	}
	free(projects);
}

void project_deleteById()			//to delete project from file using project id
{
	int id;
	project_readAll(1);
	printf("\nSelect project id to Delete project \n");
	scanf("%d",&id);
	delete_project(id);
	
}

void edit_projects()				//to edit/update project details from file
{
	int id;
        project_readAll(1);
        printf("\nSelect project id to Edit project \n");
        scanf("%d",&id);
	project_t projects;
	readbyid(&projects,id);
	int menu;
	printf("\n\nPick Choice to edit\n");
	printf("\t1-Project Name, 2-No of emp required\n");
	printf("\t3.Start date 4.End date  \n");
	printf("\t0.exit \nYour Choice:"); scanf("%d",&menu);
	printf("\n");
	if(1==menu){
	printf("Enter Project Name:");
	scanf("%s",projects.projectName);
	}	
	else if(2==menu){
        printf("Enter No of emps required:");
       // clear_input_buffer();
        scanf("%d",&projects.numOfEmpRequired);
        }
    	else if(3==menu)
    	{
        printf("Enter start date:");
        //clear_input_buffer();
        scanf("%s",projects.start_date);
    	}
    	else if(4==menu)
    	{
        printf("Enter end date:");
        scanf("%s",projects.end_date);
    	}
    else{
        printf("closing edit....\n");
 	}
   
    edit_project(projects);
}
void deleteFile()							//deleting all the project details from file
{
	project_t *projects = (project_t*)malloc(20*(sizeof(project_t)));
	int count = 0;
	project_readAllfile(projects,&count);
	for(int I=0 ; I < count ; I++)
	{
		delete_project(projects[I].projectId);
	}
	free(projects);
}

// int main() {
     
//     int menu;
// do{
// //system("clear");
// printf("\n\nPick Choice\n");
// printf("\t1.Create Project\n");
// printf("\t2.Delete Project\n\t3.Read all Project\n\t4.Edit or close Project\n\t0-Exit\n");
// printf("Your Choice:"); scanf("%d",&menu);
// printf("\n");
//     if(1==menu){
//        create_project(); 
//     }else if(2==menu){
//         project_deleteById();
//     }
//     else if(3==menu){
//         project_readAll();
//     }
//     else if(4==menu){
//         edit_projects();
//     }
//     else if(0==menu){
//         printf("Shutting down the app....\n");
//     }
//     else{
//         printf("Invalid choose....\n");
//     }
//     //clear_input_buffer();
// }
// while(((1<=menu) && (menu<=4)));

// }

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"employee_db.h"
#include"employee.h"
#include"object_t.h"
#include"myutil.h"
node_t *headEmp ;
node_t *tailEmp ;
#define DEBUG 0

#define CREATE_EMP(EMP) reademployeeinfo(&EMP);insertnode(EMP);			//preprocesser function to get employee details and add to DLL

void empOperations()													//to create ,delete ,search and display employee details
{
	employee_t employee = {};
#if DEBUG
	printf("empOperations()\n");
#endif
	
	while(1)
	{
		int choice,Id;
		printf("\n\t1-Create Employee\n\t2-Read all employee,\n\t3-Read by id,\n\t4-Delete by id,\n\t0-Exit \n\n");
		printf("Enter choice :"); scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				// reademployeeinfo(&employee);  //Read emp details  adding to file and dll
				// insertnode(employee);
				CREATE_EMP(employee);						//preprocesser function to get employee details 
				break;
			case 2:
				read_emp_from_file();						//to read employee details from file
				break;
			case 3:
				printf("Enter Id : ");scanf("%d",&Id);
				readById(Id);								//to get the employee details by employee id
				break;
			case 4:
				printf("Enter Id : ");scanf("%d",&Id);
				DeleteById(Id);								//to delete employee details by employee id
				break;
			case 0:
				return ;
				break;
			default:
				printf("Invaled is choice \n");
		}
	
	}
	
}

node_t* creatnode(employee_t Data)							//to create DLL 
{
	node_t *node = (node_t *) malloc(sizeof(node_t));
	
	memset(node,0,sizeof(node_t));
	
	node->data = Data;
	node->prev = NULL;
	node->next = NULL;
	
	return node;
}

void reademployeeinfo(employee_t * employee)				//to read the employee details 
{
	system("clear");
	printf("\n\n");
	
	int N;
	printf("Employee Id : %d\n",++employee->emp_id);
	printf("Enter employee name : "); clear_input_buffer(); fgets(employee->emp_name,256,stdin);
	printf("Enter employee password : ");  fgets(employee->emp_password,16,stdin);
	printf("Enter employee gender:");printf("Male/Female/Others(0/1/2) : ");
	scanf("%d",&N);
	
	if(N == 0)
		strcpy(employee->emp_gender , "Male");
	else if(N == 1)
		strcpy(employee->emp_gender , "Female");
	else if(N == 2)
		strcpy(employee->emp_gender , "Others");
	
	printf("Enter employee basic salary : ");scanf("%lf",&employee->emp_BasicSalary);
	strcpy(employee->emp_status,"Bench");
	
	printf("\n\n");
}

void insertnode(employee_t Data)				//to add employee node to DLL
{
	node_t * node = creatnode(Data);
	
	if(headEmp == NULL)
	{
		headEmp = node;
		tailEmp = node;
	}
	else
	{
		tailEmp->next = node;
		node->prev = tailEmp;
		tailEmp = node;
	}
	db_add_obj_into_file(&node->data);			//adding employee details to the file 
}

void read_emp_from_file()						//to display all employee details 
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
	}
	else
	{
		db_read_allobj_from_file();         	//to read all employee details from file
		printf("\n\tsuccessfully read employee details\n");
	}
}

void readById(int Id)							//to get the employee details by employee id
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
	}
	else
	{
		while(node != NULL)
		{			
			if(node->data.emp_id == Id)
			{
				db_read_oneobj_using_id(&node->data,node->data.emp_id);	//to display the employee details by employee id
				break;
			}
			node = node->prev;
		}
	}
}
void empDeallocation(int proId,int empId)		//to remove project from employee details
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
		return;
	}
	else
	{
		while(node != NULL)
		{			
			if(node->data.emp_id == empId)
			{
				int pos = -1;
				for(int i = 0;i<node->data.emp_NoOfProjects;i++ )
				{
					//printf("\tID : %d  Percentage : %d\n",node->data.allocProjId[i],node->data.allocProjPer[i]);
					if(node->data.allocProjId[i] == proId)
					{
						pos = i;
						break;
					}
				}
				if(pos>=0)
				{
					for(int i = pos ;i < node->data.emp_NoOfProjects;i++)
                    {
                        node->data.allocProjId[i] = node->data.allocProjId[i+1];
						node->data.allocProjPer[i] = node->data.allocProjPer[i+1];
                    }
					node->data.emp_NoOfProjects--;
				}
				if(node->data.emp_NoOfProjects != 0)
					strcpy(node->data.emp_status,"Active");
				else
					strcpy(node->data.emp_status,"In bench");
				db_update_obj_using_id(node->data);					//to update the employee details
				//return 1;
			}
			node = node->prev;
		}
	}
}
int empAlocation(int proId,int empId,int empPer)			 //to updated the allocated project to the employee details
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
		return 0;
	}
	else
	{
		while(node != NULL)
		{			
			if(node->data.emp_id == empId)
			{
				if(node->data.emp_NoOfProjects < 3)
				{
					node->data.allocProjId[node->data.emp_NoOfProjects] = proId;
					node->data.allocProjPer[node->data.emp_NoOfProjects] = empPer;
					node->data.emp_NoOfProjects++;
					node->data.project_allocationPercentage=0;
					for(int i = 0;i<node->data.emp_NoOfProjects;i++ )
						{
							//printf("\tID : %d  Percentage : %d\n",node->data.allocProjId[i],node->data.allocProjPer[i]);
							node->data.project_allocationPercentage+=node->data.allocProjPer[i];
						}
					node->data.emp_bonus = (BONUS * node->data.project_allocationPercentage)/100;
					//printf("Update employee bonus : %lf",node->data.emp_bonus); 
					if(node->data.emp_NoOfProjects != 0)
						strcpy(node->data.emp_status,"Active");
					else
						strcpy(node->data.emp_status,"In bench");
					db_update_obj_using_id(node->data);  //to update the employee details in file
					return 1;
					//break;
				}
				else
				{
					printf("\nCant allocate resoucre\n");
					return 0;
				}
			}
			node = node->prev;
		}
	}
}
void editEmp(int empId)					//to update employee details using employee id
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
		return;
	}
	else
	{
		while(node != NULL)
		{			
			if(node->data.emp_id == empId)
			{
				db_read_oneobj_using_id(&node->data,node->data.emp_id);	 //to read employee details using id
				int menu;
				printf("\n\nPick Choice to edit\n");
				printf("\t1-Name, 2-Password\n");
				printf("\t0.exit \nYour Choice:"); scanf("%d",&menu);
				printf("\n");	
				if(1==menu){
					printf("Enter Name:");
					scanf("%s",node->data.emp_name);
				}	
				else if(2==menu){
					printf("Enter New Passoword:");
					scanf("%s",node->data.emp_password);
					}			
				db_update_obj_using_id(node->data);			//to update the employee details
				return;
			}
			node = node->prev;
		}
	}
}


void printemployeeinformation(employee_t employee)			// to print the employee details
{
	printf("\n\n");
	printf("\tEmployrr Id : %d\n",employee.emp_id);
	//printf("\tEnter employee password : %s",employee.emp_password);
	printf("\tEnter employee name : %s",employee.emp_name);
	printf("\tEnter employee gender : %s\n",employee.emp_gender);
	printf("\tEnter employee basic salary : %lf\n",employee.emp_BasicSalary);
	printf("\tEnter employee status : %s\n",employee.emp_status);
	printf("\tEnter employee no of projects : %d\n",employee.emp_NoOfProjects);
	employee.project_allocationPercentage = 0;
	printf("\tAllocated projects and percentage : \n");
	for(int i = 0;i<employee.emp_NoOfProjects;i++ )
	{
		printf("\t\tProject ID : %d  Percentage : %d\n",employee.allocProjId[i],employee.allocProjPer[i]);
		employee.project_allocationPercentage+=employee.allocProjPer[i];
	}
	printf("\tEnter employee project allocation percentage : %d\n",employee.project_allocationPercentage);
	employee.emp_bonus=(employee.project_allocationPercentage*BONUS)/100;
	printf("\tEnter employee bonus : %lf\n",employee.emp_bonus);
	printf("\n\n");
	
}

void DeleteById(int Id)						//to delete the employee details from file and DLL
{
	system("clear");
	node_t * node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("No employees \n");
	}
	else
	{
		while(node != NULL)
		{
			if(node->data.emp_id == Id)
			{
				break;
			}
				node = node->prev;
		}
		
		
		if((node->next != NULL) && (node->prev != NULL))
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
			node->prev = NULL;
			node->next = NULL;
		}
		else if((node->prev == NULL) && (node->next != NULL))
		{
			headEmp = node->next;
			node->next->prev = NULL;
			node->next = NULL;
		}
		else if((node->next == NULL) && (node->prev != NULL))
		{
			tailEmp = node->prev;
			node->prev->next = NULL;
			node->prev = NULL;
		}
		 else             //else if((node->next == NULL) && (node->prev == NULL))
		{
			headEmp = tailEmp = NULL;
		}
		
		db_delete_obj_using_id(node->data.emp_id);			//delete employee details from file using employee id
		free(node);
	}
}

void Delete()												//to delete all the employee details from file and DLL
{
	system("clear");
	node_t * node = tailEmp;
	
	if(tailEmp == NULL)
	{
		//printf("No employees \n");
	}
	else
	{
		do
		{	
			if(tailEmp->prev != NULL)
			{
				node = tailEmp;
				tailEmp = tailEmp->prev;
				tailEmp->next = NULL;
				//db_delete_obj_in_file(&node->data);
				db_delete_obj_using_id(node->data.emp_id);
				node->prev = NULL;
				free(node);
			}
			
			if(tailEmp->prev == NULL)
			{
				node = tailEmp;
				headEmp = tailEmp = NULL;
				//db_delete_obj_in_file(&node->data);
				db_delete_obj_using_id(node->data.emp_id);
				//db_delete_obj_using_id
				free(node);
			}
			//free(node);
		} while(tailEmp != NULL);
	}
	//printf("\n\t\tDelete compleat information\n");
}

void employee_login()				//employee login function
{
	int id;
    char password[16];
    
    printf("Enter employee Id : "); scanf("%d",&id);
    printf("Enter employee password : "); scanf("%s",password);
    
	node_t *node = tailEmp;
	
	if(headEmp == NULL)
	{
		printf("\n No employees \n");
	}
	else
	{
		while(node != NULL)
		{			
			if((node->data.emp_id == id) && strcmp(node->data.emp_password , password))

			{
				int menu;
				do{
					//system("clear");
					printf("\n\nPick Choice\n");
					printf("\t1.Veiw Details\n");
					printf("\t2.Edit Details\n\t0-Exit\n"); 
					printf("Your Choice:"); scanf("%d",&menu);
					
					printf("\n");
					if(1==menu){
						db_read_oneobj_using_id(&node->data,node->data.emp_id);
					}else if(2==menu){
						editEmp(node->data.emp_id);
					}
					else{
						printf("Invalid choose....\n");
					}
					//clear_input_buffer();
				
				}
				while(((1<=menu) && (menu<=2)));
				//db_read_oneobj_using_id(&node->data,node->data.emp_id);
				break;
			}
			node = node->prev;
		}
	}
}

// void clear_input_buffer()
// {
//     while(getchar() != '\n');
// }

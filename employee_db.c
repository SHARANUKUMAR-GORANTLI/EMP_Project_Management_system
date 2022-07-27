#include"employee_db.h"
#include<stdio.h>
#include<string.h>

void db_add_obj_into_file(employee_t * empaddr)         //adding employee details to the file DB
{
	char filename [] = "employee.dat";
	FILE* out = fopen(filename,"ab");
	if(out == NULL)
	{
		printf("FILE ERROR..!");
		return;
	}
	else
	{
		fwrite(empaddr, sizeof(employee_t), 1, out);
	}
	fclose(out);
}

void db_read_allobj_from_file()                         //to read all employee details from file DB
{
	char filename [] = "employee.dat";
	employee_t temp;
	FILE* in = fopen(filename,"rb");
	if(in == NULL)
	{
		printf("FILE ERROR..!");
		return;
	}
	while(fread(&temp,1,sizeof(employee_t),in))
	{
		printemployeeinformation(temp);                 //to print employee details
	}
	fclose(in);
}

void db_read_oneobj_using_id(employee_t * empaddr,int emp_id)   //to display the employee details by employee id
{
	employee_t employee;
    
    char fileName[] = "employee.dat";
    FILE* in = fopen(fileName,"rb");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return ;
    }
    while(fread(&employee,1,sizeof(employee_t),in))
	{
        if(employee.emp_id == emp_id)
	{
        	printemployeeinformation(employee);         //to print employee details
        	break;
        }
    }
    fclose(in);
}

void db_update_obj_using_id(employee_t empinfo)         //to edit/update the employee details
{
	int I = 0; 
    employee_t employee;
    
    char fileName[] = "employee.dat";
    FILE* in = fopen(fileName,"rb+");
    if(in == NULL){
        printf("FILE ERROR.\n");
        return;
    }
    while(fread(&employee,1,sizeof(employee_t),in))
	{
		I++;
        if(employee.emp_id == empinfo.emp_id){        	
        	break;
        }        
    }
    if(I > 0){
    	fseek(in,(I-1)*sizeof(employee_t),SEEK_SET);
    	fwrite(&empinfo,1,sizeof(employee_t),in);
    }
    fclose(in);
}

void db_delete_obj_using_id(int Id)                 //to delete employee details based on id from file 
{
	employee_t employee;
    
    char fileName[] = "employee.dat";
    char tempFileName[] = "emptemp.dat";
    FILE* in = fopen(fileName,"r");
    FILE* out = fopen(tempFileName,"w");
    if(in == NULL)
	{
        printf("(in)FILE ERROR.\n");
        return;
    }
    if(out == NULL)
	{
        printf("(out)FILE ERROR.\n");
        return;
    }
    while(fread(&employee,1,sizeof(employee_t),in))
	{
        if(employee.emp_id != Id)
        {
        	fwrite(&employee,1,sizeof(employee_t),out);
        }        
    }    
    fclose(out);
    fclose(in); 
    remove(fileName);               
    rename(tempFileName,fileName);
}

// void db_delete_obj_in_file(employee_t* empaddr)             //to delete all the employee details from file
// {
// 	employee_t employee;
    
//     char fileName[] = "employee.dat";
//     char tempFileName[] = "emptemp.dat";
//     FILE* in = fopen(fileName,"r");
//     FILE* out = fopen(tempFileName,"w");
//     if(in == NULL)
// 	{
//         printf("(in)FILE ERROR.\n");
//         return;
//     }
//     if(out == NULL)
// 	{
//         printf("(out)FILE ERROR.\n");
//         return;
//     }
//     while(fread(&employee,1,sizeof(employee_t),in))
// 	{
//         if(employee.emp_id != empaddr->emp_id)
// 		{        	
//         	fwrite(&employee,1,sizeof(employee_t),out);
//         }        
//     }    
//     fclose(out);
//     fclose(in); 
//     remove(fileName);
//     rename(tempFileName,fileName);
// }



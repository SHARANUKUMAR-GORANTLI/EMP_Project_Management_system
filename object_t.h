#pragma once
enum status {active = 0, completed = 1};
struct _project_t{                              //structure to store project details
 int status;
 int projectId;
 char projectName[256];
 int numOfEmpRequired;
 char start_date[20];
 char  end_date[20];
 int allocEmpId[10],allocEmpPer[10];
 int numOfEmpAllocated,allocatedper;
};
typedef struct _project_t project_t;

struct _admin_t                                  //structure to store admin details
{
	int id;
	char password[256];
	char adminname[256];
};
typedef struct _admin_t admin_t;

typedef struct _employee_t                       //structure to store employee details
{
    int emp_id;
    char emp_password[16];
    char emp_name[256];
    char emp_gender[16];
    double emp_BasicSalary;
    char emp_status[32];
    int emp_NoOfProjects;
    int project_allocationPercentage;
    double emp_bonus;
	int allocProjId[3],allocProjPer[3];
    
}employee_t;

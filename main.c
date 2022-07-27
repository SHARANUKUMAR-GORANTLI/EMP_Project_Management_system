#include"admin_main.h"
#include"myutil.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"employee.h"
#include"dlist.h"
#define DEBUG 0
int main(){
#if DEBUG
	printf("Main \n");
#endif
    int menu;
    do{
        //system("clear");
        printf("\n\nPick Choice\n");
        printf("\t1.Admin Login\n");
        printf("\t2.Employee Login\n\t3.Add Admin\n\t4.Read all admin\n\t0-Exit\n"); 
        printf("Your Choice:"); scanf("%d",&menu);
        
        printf("\n");
        if(1==menu){
            login();                        //admin login
        }else if(3==menu){
            create_admin();                 //creating new admin
        }
        else if(4==menu){
            readAllAdmin();                 //readall admin details
        }
        else if(0==menu){
            printf("Shutting down the app....\n");
        }
        else if(2==menu){
            employee_login();               //employee login
        }
        else{
            printf("Invalid choose....\n");
        }
        //clear_input_buffer();
       
    }
    while(((1<=menu) && (menu<=4)));
    Delete();                               //deleting all the employee details
    deleteFile();                           //deleting all the project details
	return EXIT_SUCCESS;
}

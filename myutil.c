#include"myutil.h"
#include<stdio.h>
void clear_input_buffer(void){   //to wait until new line
    while(getchar() != '\n');
}
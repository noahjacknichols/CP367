#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int calculateBirthday(int day, int month){

}


int main(int argc, char *argv[]){

    //printf(system("who")); //find easy way to delimit this
    int day, month;
    printf("Enter your day of birth (DD)");
    scanf("%d", &day);
    printf("Enter your month of birth (MM)");
    scanf("%d", &month);
    int birthday = calculateBirthday(day, month);
    

}
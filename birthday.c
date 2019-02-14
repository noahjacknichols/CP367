#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

long int calculateEpoch(long int day, long int month){
    //calculates the epochTime from the given day and month
    printf("day:%ld\n", day);
    printf("month:%ld\n", month);
    long int epochTime = (day) * 86400 + (month) * 2629743;
    return epochTime;

}

long int days(long int a, long int b){
    printf("a:%ld\n", a);
    printf("b: %ld\n", b);
    long int timeLeft = a-b;
    printf("timeLeft:%ld\n", a-b);
    int days = ceil((((timeLeft)/60)/60));
    printf("days:%d, calculated:\n", days);
    return days;
}

int calculateBirthday(int day, int month, int sysday, int sysmonth,int year, int *months){
    int found = 0;
    int days = 0;
    int i = sysmonth;
    int j = sysday;
    month -=1; //accounting for tm->month is 0 to 11, yet we put in 1-12
    int wrapAround = 0;
    int newMonth = 0;

    while(!found){
        if(year %4 == 0 && year %100 != 0){
           months[1] = 29;
        }else{
           months[1] = 28;
        }
     
     
        if(wrapAround){
            i = 0;
        }
        for(i; i < 12; i++){
            if(newMonth){
                j = 1;
                days++;
            }
            for(j; j < months[i]; j++){
                
                if(i == month && j == day){

                    return days; //if we are on the birthday, return days
                }
                if(!found){
                    days++;
                }
                newMonth = 1;
            }
        }
        wrapAround = 1;
        year++;
    }
}


int main(int argc, char *argv[]){
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //used for convenience with handling user input for days
    time_t timeInSeconds;
   
    
    long int offset;
    struct tm *info;
    int correctInput = 1;

    if(argc >1){
        offset = atol(argv[1]); //input was given;
    }
    if(offset > 29219){ //check to see if user has put in more than 29219 => 80 years in days
        correctInput = 0;
        printf("sorry, you put in more than 80 years.\n");
    }

    if(correctInput){
        timeInSeconds = time(NULL) + offset *86400;
        info = localtime(&timeInSeconds);
        char buf[32];
        char userID[32];
        size_t size = 32;

        //greet user
        getlogin_r(userID, size);
        printf("hello, %s\n", userID);
        
        //print date with or without offset
        sprintf(buf, "date -d @%d", timeInSeconds);
        system(buf);

        //prompt for user input
        long int day, month;
        printf("Enter your day of birth (DD):");
        scanf("%ld", &day);
        printf("Enter your month of birth (MM):");
        scanf("%ld", &month);
        if(month <= 12 && day <= 32){ //user input is correct

            int days = calculateBirthday(day, month, info->tm_mday, info->tm_mon, info->tm_year, months);
            if(days == 0){ //check if birthday
                printf("Happy Birthday, %s!\n", userID);
            }else{ //print the number of days until birthday
                printf("There are %ld days until your birthday.\n", days);
            }
        }else{ //if user input isn't a real date, then print invalid
            printf("Sorry, it seems the date you put in is invalid.\n");
        }
    }
}

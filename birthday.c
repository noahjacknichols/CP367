#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <math.h>

 const long int YEAR_IN_SECONDS = 31556926;
const long int GMT = 14 * 3600;

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
    int wrapAround = 0;
    int newMonth = 0;
    printf("day:%d, month %d, sysday:%d, sysmonth:%d\n", day,month,sysday,sysmonth);
    while(!found){
        if(year %4 == 0 && year %100 != 0){
           months[1] = 29;
        }else{
           months[1] = 28;
        }
     
     
        if(wrapAround){
            i = 1;
        }
        for(i; i < 12; i++){
            if(newMonth){
                j = 1;
                days++;
            }
            for(j; j < months[i]; j++){
                printf("i:%d, j:%d\n", i,j);
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
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t timeInSeconds;
   
    


    long int offset = 0;
    timeInSeconds = time(NULL);
 
    if(argc > 1){
        offset = 86400 * atoi(argv[1]);
        timeInSeconds = timeInSeconds + offset;
    }
    struct tm *info;
    info = localtime(&timeInSeconds);
    

//     long int temp = timeInSeconds;
//     int year = 0;
//     while(temp > 0){
//         year++;
//         temp -= YEAR_IN_SECONDS;
//     }
//     year += 1970;
//     if(year % 400 == 0 && year % 100 != 0){
//         months[1] = 29; //account for leap year 
//     }
    char buf[32];
    char buf2[32];
    char userID[32];
    char birthdayEpoch[32];
    char currentEpoch[32];

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

    snprintf(birthdayEpoch, 32, "%d-%d-%d", month, day, year); //get mm-dd-yyyy format 
    sprintf(buf2, "date --d %s +'%s'");

    if(month <= 12 && day <= 32){ //user input is correct
        
        long int strippedEpoch = timeInSeconds % 31556926; //strip epoch time of the years for convenience
        long int sysmonth = ceil(strippedEpoch/3600/24/12) -1; //calculate # months, subtract 1 to account for correct month format
        long int sysday = ceil((strippedEpoch%2629743)/86400); //calculate # days
        printf("calculated month:%ld, day:%ld\n", sysmonth,sysday);
        int days = calculateBirthday(day, month, info.tm_mday, info.tm_mon, months);
        if(days == 0){
            printf("Happy Birthday, %s!\n", userID);
        }else{
            // long int untilBirthday = 0; //initalize value in case
            //     long int systime = calculateEpoch(sysday, sysmonth);
            //     long int time = calculateEpoch(day,month);
            // int isBehind = 0;
            // if(time < systime){ //if the current day is after the birthday, we have a different handler
            //     isBehind = 1;
            // }
            // if(isBehind){ 
            //     //the birthday is behind todays date
            //     printf("birthday < time\n");
            //     systime = calculateEpoch(sysday, sysmonth);
            //     month+=12; // offset by a year
            //     time = calculateEpoch(day,month);
                
            //     untilBirthday = (time - systime)/86400;
            // }else{
            //     //birthday after today's date
            //     systime = calculateEpoch(sysday, sysmonth);
            //     time = calculateEpoch(day,month);
            //     untilBirthday = (time - systime)/86400;
            // }
            
            printf("There are %ld days until your birthday.\n", days);
        }
    }else{
        printf("Sorry, it seems the date you put in is invalid.\n");
    }

}

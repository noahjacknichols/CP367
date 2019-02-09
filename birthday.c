#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <math.h>
 const long int YEAR_IN_SECONDS = 31556926;


long int calculateBirthday(long int day, long int month, long int currentYear){
    //calculates the epochTime from the given day and month
    printf("day:%ld\n", day);
    printf("month:%ld\n", month);
    printf("Year:%ld\n", 1970+currentYear);
    long int epochTime = day * 86400 + month * 2629743 + currentYear * YEAR_IN_SECONDS;
    return epochTime;

}

long int days(long int a, long int b){
    printf("a:%ld\n", a);
    printf("b: %ld\n", b);
    long int timeLeft = abs(a -b);
    long int days = ceil((((timeLeft)/60)/60)/24);
    return days;
}


int main(int argc, char *argv[]){
    time_t timeInSeconds;
    
    timeInSeconds = time(NULL);

    //uid_t id = geteuid(getuid());
    char buf[32];
    char userID[32];
    size_t size = 32;
    //greet user
    getlogin_r(userID, size);
    printf("hello, %s\n", userID);
    
    //print date with or without offset
    sprintf(buf, "date -d @%d", timeInSeconds);
    system(buf);
    long int temp = timeInSeconds;
    long int currentYear = 0;
    while(temp - YEAR_IN_SECONDS > 0){
        currentYear++;
        temp = temp - YEAR_IN_SECONDS;
    }
    //printf("calculated currentYear to be: %d\n", currentYear);
    
    long int day, month;
    printf("Enter your day of birth (DD):");
    scanf("%ld", &day);
    printf("Enter your month of birth (MM):");
    scanf("%ld", &month);

    if(month <= 12 && day <= 32){ //user input is correct
        long int birthday = calculateBirthday(day, month, currentYear);
        if(days(birthday, timeInSeconds) == 0){
            printf("Happy Birthday, %s!\n", userID);
        }else{
            long int untilBirthday = 0; //initalize value in case
            if(birthday > timeInSeconds){
                printf("birthday > time\n");
                
                untilBirthday = days(birthday, timeInSeconds);
            }else{
                printf("birthday < time\n");
                untilBirthday = days(birthday + YEAR_IN_SECONDS, timeInSeconds);
            }
            printf("There are %ld days until your birthday.\n", untilBirthday);
        }
    }else{
        printf("Sorry, it seems the date you put in is invalid.\n");
    }

}
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>


int main(void) {
    char *dir_name = ".";
    char file_name[10];
    char buffer[5];
    char command[128] = "code ";
    FILE *fp;

    // Get a list of all files in the directory.
    DIR *dp = opendir(dir_name);
    if (dp == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }
    
    // Get the current time.
    time_t now = time(NULL);

    // Convert the current time to a struct tm.
    struct tm *local_time = localtime(&now);
    
    itoa(local_time->tm_year+1900, buffer, 10);
    strcat(file_name, buffer);
    strcat(file_name, "-");

    if(local_time->tm_mon+1 < 10)
        strcat(file_name, "0");
    itoa(local_time->tm_mon+1, buffer, 10);
    strcat(file_name, buffer);
    strcat(file_name, "-");

    if(local_time->tm_mday+1 < 10)
        strcat(file_name, "0");
    itoa(local_time->tm_mday, buffer, 10);
    strcat(file_name, buffer);
    strcat(file_name, ".md");

    strcat(command, file_name);
    
    
    fp = fopen(file_name, "a+");

    if (fp == NULL) printf("Error opening file %s.\n", file_name);
    system("code .");
    system(command);

    closedir(dp);
    return 0;
}


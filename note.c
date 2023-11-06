#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>


int main(void) {
    char *dir_name = ".";
    char _file_name[10];
    char _buffer[5];
    char _command[128] = "code ";
    
    char _1st_line[16] = "# ";
    char _2nd_line[16] = "###### ";

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
    
    itoa(local_time->tm_year+1900, _buffer, 10);
    strcat(_file_name, _buffer);
    strcat(_file_name, "-");

    if(local_time->tm_mon+1 < 10)
        strcat(_file_name, "0");
    itoa(local_time->tm_mon+1, _buffer, 10);
    strcat(_file_name, _buffer);
    strcat(_file_name, "-");

    if(local_time->tm_mday+1 < 10)
        strcat(_file_name, "0");
    itoa(local_time->tm_mday, _buffer, 10);
    strcat(_file_name, _buffer);

    strcat(_1st_line, _file_name);
    strcat(_1st_line, "\n");

    strcat(_file_name, ".md");

    strcat(_command, _file_name);
    
    
    fp = fopen(_file_name, "a+");

    if (fp == NULL) printf("Error opening file %s.\n", _file_name);


    // Write text to the file
    fprintf(fp, _1st_line);
    fprintf(fp, _2nd_line);

    system("code .");
    system(_command);

    closedir(dp);
    return 0;
}


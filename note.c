#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

#define TITLE   "# "
#define TAG     "###### "
#define DASH    "-"
#define FILE_NAME_LENGTH 13
#define TITLE_NAME_LENGTH 10
#define COMMAND "code ./"


int main(void) {
    char *dir_name = ".";
    char _title_name[TITLE_NAME_LENGTH+1];
    char _buffer[FILE_NAME_LENGTH];
    char _command[20];
    
    int  year = 0;
    int  month = 0;
    int  date = 0;
    int  buffer_count = 0;

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

    year = local_time->tm_year+1900;
    month = local_time->tm_mon+1;
    date = local_time->tm_mday;
    
    // ----- print date into buffer -----
    buffer_count = snprintf(_buffer, FILE_NAME_LENGTH,"%d", year);
    buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, DASH);

    if(month < 10)
        buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, "0");
    buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, "%d", month);
    buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, DASH);


    if(date < 10)
        buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, "0");
    buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, "%d", date);

    printf("\n");


    // ----- copy file name to title -----
    memcpy(_title_name, _buffer, TITLE_NAME_LENGTH);
    strcat(_title_name, "\0"); // add \0 into tutle buffer
    

    buffer_count += snprintf(_buffer+buffer_count, FILE_NAME_LENGTH, "%s", ".md");

    
    // ----- create file -----
    fp = fopen(_buffer, "a+");
    if (fp == NULL) printf("Error opening file %s.\n", _buffer);


    // Write text to the file
    // ----- create title -----
    fprintf(fp, "%s", TITLE);
    fprintf(fp, "%s\n", _title_name);


    // ----- create date tag mm/dd -----
    fprintf(fp, "%s", TAG);
    if(month<10)
        fprintf(fp, "0");
    fprintf(fp, "%d", month);
    if(date<10)
        fprintf(fp, "0");
    fprintf(fp, "%d\n", date);
    
    // ----- create empty tag -----
    fprintf(fp, "%s\n", TAG);
    fprintf(fp, "%s\n", TAG);
    fprintf(fp, "%s\n", TAG);


    // ----- create terminal command -----
    strncat(_command, COMMAND, 8);
    strncat(_command, _buffer,13);
    system(_command);

    closedir(dp);
    return 0;
}


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>

#define TITLE   "# "
#define TAG     "###### "
#define DASH    "-"
#define FILE_NAME_LENGTH    13
#define DIR_NAME_LENGTH     128
#define TITLE_NAME_LENGTH   10
#define COMMAND "code ./"

#define DIRNAME "home/yushun.wang/Desktop/Notes/MyNotes/"

int main(void) {
    char _title_name[TITLE_NAME_LENGTH+1] = {0};
    char _filename[FILE_NAME_LENGTH] = {0};
    char _dirname[DIR_NAME_LENGTH] = {0};
    char _command[DIR_NAME_LENGTH] = {0};
    
    int year = 0;
    int month = 0;
    int date = 0;
    int buffer_count = 0;

    int error = 0;

    FILE *fp;
    DIR *dp;

    // Get a list of all files in the directory.
    dp = opendir(DIRNAME);
    if (dp == NULL) {
        error= errno;
        printf("Error in opening \"%s\"\n", DIRNAME);
        printf("Error: %s\n", strerror( error ) );
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
    buffer_count = snprintf(_filename, FILE_NAME_LENGTH,"%d", year);
    buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, DASH);

    if(month < 10)
        buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, "0");
    buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, "%d", month);
    buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, DASH);


    if(date < 10)
        buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, "0");
    buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, "%d", date);

    printf("\n");


    // ----- copy file name to title -----
    memcpy(_title_name, _filename, TITLE_NAME_LENGTH);
    strcat(_title_name, "\0"); // add \0 into title buffer
    

    buffer_count += snprintf(_filename+buffer_count, FILE_NAME_LENGTH, "%s", ".md");

    strncat(_dirname, DIRNAME, sizeof(DIRNAME));
    strncat(_dirname, _filename, FILE_NAME_LENGTH);
    // ----- create file -----
    fp = fopen(_dirname, "a+");
    if (fp == NULL) {
        error= errno;
        printf("Error opening file \"%s\"\n", _dirname);
        printf("Error: %s\n", strerror( error ) );
        closedir(dp);
        return 1;
    }


    // Write text to the file
    // ----- create title -----
    fprintf(fp, "%s", TITLE);
    fprintf(fp, "%s\n", _title_name);

    printf("dir:%s\n", _dirname);
    printf("file:%s\n", _filename);
    printf("title:%s\n", _title_name);

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
    strncat(_command, _dirname,128);
    system(_command);

    printf("Executing... \"%s\"\n", _command);
    system("exit");

    fclose(fp);
    closedir(dp);
    return 0;
}
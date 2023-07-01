#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <dirent.h>
#define INIT_COMMAND char##var

int main(int argc, char** argv) {
    if (argc < 2){        
        printf("Error. No input search.\n");
        return 1;
    }
    char *dir_name = ".";
    char *file_name;
    char search_string[64];
    char search_target[64];
    char command[128] = "code ";

    FILE *fp;
    file_name = calloc(0, 13);
    argc = argc;

    // Get a list of all files in the directory.
    struct dirent *dir;
    DIR *dp = opendir(dir_name);
    if (dp == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }
    strcpy (search_string,"###### ");
    strcpy (search_target, *(argv+1));
    strcat (search_string, search_target);
    printf ("search_string = %s\n", search_string);
    
    // Iterate over the list of files and open each one.
    while ((dir = readdir(dp)) != NULL) {
        file_name = dir->d_name;
        
        fp = fopen(file_name, "r");
        if (fp == NULL) {
        printf("Error opening file %s.\n", file_name);
        } 
        else {
            // Iterate over the file, looking for the search string.
            while (!feof(fp)) {
            char ch;
            ch = fgetc(fp);
                if (ch == search_string[0]) {
                    // Check if the next few characters match the search string.
                    size_t i;
                    for (i = 1; i < strlen(search_string); i++) {
                        if (fgetc(fp) != search_string[i]) {
                            break;
                        }
                    }
                    if (i == strlen(search_string)) {
                        // The search string was found!
                        strcat(command, file_name);
                        printf("%s is found.\n", search_string);
                        system(command);
                        
                        memset(command, 0, 128);
                        command[0] = 'c';
                        command[1] = 'o';
                        command[2] = 'd';
                        command[3] = 'e';
                        command[4] = ' ';
                        break;
                    }
                    else printf("Nothing found.\n");
                }
            }
            fclose(fp);
            printf("%s is opened.\n", file_name);
        }
    }

    closedir(dp);
    return 0;
}


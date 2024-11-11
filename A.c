Q.1) Display all the files from the current directory which are created in a particular month

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dp = opendir(".");
    char month[20];
    struct tm *timeinfo;
    int target_month;

    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Enter the month (1-12): ");
    scanf("%d", &target_month);

    printf("Files created in month %d:\n", target_month);
    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            timeinfo = localtime(&fileStat.st_ctime);
            if (timeinfo->tm_mon + 1 == target_month) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dp);
    return 0;
}


Output:
Enter the month (1-12): 5
Files created in month 5:
file1.txt
image.jpg

Q.2) Write a C program to create n child processes. When all n child processes terminate, display the total cumulative time children spent in user and kernel mode.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int n;
    pid_t pid;
    struct rusage usage;
    long total_user_time = 0, total_sys_time = 0;

    printf("Enter number of child processes to create: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid == 0) {
           
            printf("Child %d started\n", i + 1);
            sleep(2); 
            exit(0);
        }
    }


    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

 
    for (int i = 0; i < n; i++) {
        getrusage(RUSAGE_CHILDREN, &usage);
        total_user_time += usage.ru_utime.tv_sec;
        total_sys_time += usage.ru_stime.tv_sec;
    }

    printf("Total cumulative time spent by children:\n");
    printf("User mode time: %ld seconds\n", total_user_time);
    printf("Kernel mode time: %ld seconds\n", total_sys_time);

    return 0;
}


Output:
Enter number of child processes to create: 3
Child 1 started
Child 2 started
Child 3 started
Total cumulative time spent by children:
User mode time: 6 seconds
Kernel mode time: 3 seconds

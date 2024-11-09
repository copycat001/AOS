#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void display_files_in_month(int target_month, int target_year) {
    DIR *dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir failed");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".."
        if (entry->d_name[0] == '.') {
            continue;
        }

        // Get the file information using stat()
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat failed");
            continue;
        }

        // Get the modification time of the file
        struct tm *mod_time = localtime(&file_stat.st_mtime);
        int file_month = mod_time->tm_mon + 1;  // tm_mon is 0-based (0 = January)
        int file_year = mod_time->tm_year + 1900;  // tm_year is years since 1900

        // Compare with the target month and year
        if (file_month == target_month && file_year == target_year) {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);  // Close the directory after reading
}

int main() {
    int month, year;

    // Ask the user for the target month and year
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
    printf("Enter the year (e.g., 2023): ");
    scanf("%d", &year);

    if (month < 1 || month > 12) {
        fprintf(stderr, "Invalid month! Please enter a value between 1 and 12.\n");
        return 1;
    }

    // Display files created/modified in the given month and year
    display_files_in_month(month, year);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>

// Function to simulate some work in the child process
void child_work() {
    sleep(2);  // Simulate some CPU work by sleeping for 2 seconds
}

int main() {
    int n;  // Number of child processes
    printf("Enter the number of child processes: ");
    scanf("%d", &n);

    pid_t pid;
    struct tms start_time, end_time;
    clock_t start_clock, end_clock;

    // Create child processes
    for (int i = 0; i < n; i++) {
        pid = fork();
        
        if (pid < 0) {
            // Error in fork
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) started...\n", i + 1, getpid());
            child_work();  // Simulate some work
            printf("Child %d (PID: %d) finished.\n", i + 1, getpid());
            exit(0);  // Child exits after work
        }
    }

    // Parent process waits for all children to terminate
    for (int i = 0; i < n; i++) {
        wait(NULL);  // Wait for each child to terminate
    }

    // Get the start time for the parent process
    start_clock = times(&start_time);

    // Parent process: wait for all child processes to finish and then get times
    end_clock = times(&end_time);

    // Calculate the total user and system time spent by children
    clock_t total_user_time = end_time.tms_cutime - start_time.tms_cutime;
    clock_t total_system_time = end_time.tms_cstime - start_time.tms_cstime;

    printf("\nTotal cumulative time spent by children:\n");
    printf("Total User CPU time: %ld clock ticks\n", total_user_time);
    printf("Total System CPU time: %ld clock ticks\n", total_system_time);

    return 0;
}
*/

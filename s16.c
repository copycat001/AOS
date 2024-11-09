#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char *dir_path = ".";  // Current directory
    int month;

    // Get the month from the user (1-12)
    printf("Enter the month (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid month input. Please enter a valid month (1-12).\n");
        return 1;
    }

    // Open the current directory
    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read and check each file in the directory
    printf("Files created in month %d:\n", month);
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get the file status using stat()
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Extract the month from the file's last modification time
        struct tm *time_info = localtime(&file_stat.st_mtime);
        if (time_info == NULL) {
            perror("localtime");
            continue;
        }

        // Check if the file's modification month matches the input month
        if (time_info->tm_mon + 1 == month) {  // tm_mon is 0-indexed
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT\n");
}

void handle_sigquit(int sig) {
    printf("My DADDY has Killed me!!!\n");
    exit(0);
}

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process: Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Child process waits indefinitely for signals
        while (1) {
            pause();
        }
    } else {
        // Parent process
        int elapsed_time = 0;
        
        while (elapsed_time < 30) {
            sleep(3);
            elapsed_time += 3;

            if (elapsed_time == 30) {
                kill(child_pid, SIGQUIT);  // Send SIGQUIT after 30 seconds
            } else {
                kill(child_pid, (elapsed_time % 2 == 0) ? SIGHUP : SIGINT);  // Alternate SIGHUP and SIGINT
            }
        }

        // Wait for child process to terminate
        wait(NULL);
        printf("Parent process exiting.\n");
    }

    return 0;
}
*/

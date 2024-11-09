#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int file_exists_in_directory(const char *filename) {
    DIR *dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir failed");
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            closedir(dir);  // Close the directory after finding the file
            return 1;  // File found
        }
    }

    closedir(dir);  // Close the directory after checking all entries
    return 0;  // File not found
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // Loop through each file name passed as command-line argument
    for (int i = 1; i < argc; i++) {
        if (file_exists_in_directory(argv[i])) {
            printf("File '%s' is present in the current directory.\n", argv[i]);
        } else {
            printf("File '%s' is NOT present in the current directory.\n", argv[i]);
        }
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// Function to handle SIGHUP signal in the child
void handle_sighup(int sig) {
    printf("Child received SIGHUP\n");
}

// Function to handle SIGINT signal in the child
void handle_sigint(int sig) {
    printf("Child received SIGINT\n");
}

// Function to handle SIGQUIT signal in the child
void handle_sigquit(int sig) {
    printf("My Papa has Killed me!!!\n");
    exit(0);  // Terminate the child process
}

int main() {
    pid_t pid;

    // Fork to create the child process
    pid = fork();

    if (pid < 0) {
        // Error in forking
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Child process code

        // Set up signal handlers for SIGHUP, SIGINT, and SIGQUIT
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Keep the child process running to handle signals
        printf("Child process (PID: %d) is waiting for signals...\n", getpid());
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process code

        printf("Parent process (PID: %d) is sending signals...\n", getpid());

        // Parent sends SIGHUP and SIGINT alternately every 3 seconds
        for (int i = 1; i <= 5; i++) {
            if (i % 2 != 0) {
                // Send SIGHUP
                kill(pid, SIGHUP);
                printf("Parent sent SIGHUP to child (PID: %d)\n", pid);
            } else {
                // Send SIGINT
                kill(pid, SIGINT);
                printf("Parent sent SIGINT to child (PID: %d)\n", pid);
            }

            sleep(3);  // Wait for 3 seconds before sending the next signal
        }

        // After 15 seconds, send SIGQUIT to terminate the child
        sleep(3);  // Wait for 3 more seconds
        kill(pid, SIGQUIT);  // Send SIGQUIT
        printf("Parent sent SIGQUIT to child (PID: %d)\n", pid);

        // Wait for child to terminate
        wait(NULL);
    }

    return 0;
}
*/ 

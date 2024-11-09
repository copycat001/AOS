#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int sig) {
    // A simple handler to catch the signals for the child process
    if (sig == SIGSTOP) {
        printf("Child process suspended\n");
    } else if (sig == SIGCONT) {
        printf("Child process resumed\n");
    }
}

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        signal(SIGSTOP, handler); // Set handler for SIGSTOP
        signal(SIGCONT, handler); // Set handler for SIGCONT

        printf("Child process: PID = %d, running...\n", getpid());

        // Infinite loop to keep child alive and ready for suspension/resumption
        while (1) {
            sleep(1);
        }
    } else {
        // Parent process
        printf("Parent process: PID = %d, will suspend and resume child process.\n", getpid());

        // Give the child some time to start executing
        sleep(2);

        // Suspend the child process using SIGSTOP
        printf("Parent: Suspending child process...\n");
        kill(pid, SIGSTOP);

        // Give the child some time in suspended state
        sleep(3);

        // Resume the child process using SIGCONT
        printf("Parent: Resuming child process...\n");
        kill(pid, SIGCONT);

        // Wait for the child to exit (the child never exits in this example)
        wait(NULL);
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];  // Prefix to search for
    size_t prefix_len = strlen(prefix);

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    printf("Files beginning with \"%s\":\n", prefix);

    // Read entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry name starts with the specified prefix
        if (strncmp(entry->d_name, prefix, prefix_len) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);
    return 0;
}
//cc s13.c -o s13
//./s13 foo
*/

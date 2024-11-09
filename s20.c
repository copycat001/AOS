#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler for SIGSTOP and SIGCONT (not strictly needed, but can be used to print messages)
void handle_signal(int sig) {
    if (sig == SIGSTOP) {
        printf("Child process suspended.\n");
    }
    if (sig == SIGCONT) {
        printf("Child process resumed.\n");
    }
}

int main() {
    pid_t pid;

    // Set up signal handlers (optional)
    signal(SIGSTOP, handle_signal);
    signal(SIGCONT, handle_signal);

    // Create child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  // Child process
        // Perform some task in the child process
        for (int i = 0; i < 5; i++) {
            printf("Child process running... %d\n", i + 1);
            sleep(1);  // Simulate work
        }
        printf("Child process completed.\n");
    } else {  // Parent process
        // Parent suspends the child process after a delay
        sleep(2);  // Let the child run for 2 seconds
        printf("Parent process suspending child...\n");
        kill(pid, SIGSTOP);  // Suspend the child process
        
        sleep(2);  // Parent sleeps for 2 seconds before resuming the child
        
        printf("Parent process resuming child...\n");
        kill(pid, SIGCONT);  // Resume the child process
        
        // Wait for child process to finish
        wait(NULL);
        printf("Parent process ends.\n");
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void file_type(struct stat st) {
    // Check the file type
    if (S_ISREG(st.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("FIFO (Named pipe)\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown file type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;

    // Get file status using stat()
    if (stat(argv[1], &st) == -1) {
        perror("stat failed");
        return 1;
    }

    // Display the file type
    file_type(st);

    return 0;
}
*/

//Q1
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
void print_file_type(struct stat st) {
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        struct stat st;
        if (stat(argv[i], &st) == -1) {
            perror("stat failed");
            continue;  
        }
        printf("File: %s\n", argv[i]);
        printf("Inode number: %ld\n", (long) st.st_ino);  
        print_file_type(st);  
        printf("\n");
    }
    return 0;
}
/*
//Q2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
// Signal handler for SIGALRM
void handle_alarm(int sig) {
    // This function is called when SIGALRM is caught
    printf("Alarm fired: SIGALRM received in parent process!\n");
}

int main() {
    pid_t pid;

    // Set up the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    // Create a child process using fork()
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return EXIT_FAILURE;
    }

    if (pid > 0) {
        // Parent process code
        printf("Parent process (PID: %d) waiting for signal...\n", getpid());

        // Sleep for a while to allow child to send signal
        sleep(3);

        // Parent process waits for SIGALRM signal to be handled
        printf("Parent process is done waiting.\n");
        // Continue running so the signal handler has time to execute
        sleep(2);

    } else if (pid == 0) {
        // Child process code
        printf("Child process (PID: %d) sending SIGALRM to parent...\n", getpid());

        // Sleep for 1 second to allow parent to set up signal handler
        sleep(1);

        // Send SIGALRM signal to parent (PID is passed as the first argument)
        kill(getppid(), SIGALRM);

        // Child process exits
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}
*/

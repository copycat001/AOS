#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File Type: Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File Type: Character Device\n");
    } else if (S_ISBLK(mode)) {
        printf("File Type: Block Device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File Type: FIFO (Named Pipe)\n");
    } else if (S_ISLNK(mode)) {
        printf("File Type: Symbolic Link\n");
    } else if (S_ISSOCK(mode)) {
        printf("File Type: Socket\n");
    } else {
        printf("File Type: Unknown\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    const char *filename = argv[1];

    // Get file status using stat()
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // Print inode number
    printf("Inode Number: %ld\n", (long) file_stat.st_ino);

    // Print file type
    print_file_type(file_stat.st_mode);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// Global variable to store the child's PID
pid_t child_pid = -1;

// Signal handler for child process death (SIGCHLD)
void sigchld_handler(int sig) {
    int status;
    if (child_pid > 0) {
        // Wait for the child process to exit and retrieve its exit status
        waitpid(child_pid, &status, WNOHANG);
        printf("Child process terminated.\n");
    }
}

// Signal handler for alarm signal (SIGALRM)
void sigalrm_handler(int sig) {
    if (child_pid > 0) {
        // If the child hasn't finished within 5 seconds, kill it
        printf("Child process is taking too long. Killing the child.\n");
        kill(child_pid, SIGKILL);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    // Set up signal handlers
    signal(SIGCHLD, sigchld_handler); // Handle child process termination
    signal(SIGALRM, sigalrm_handler); // Handle alarm after 5 seconds

    // Fork the child process
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Child process: execute the command provided as argument
        printf("Child process executing: ");
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");

        // Execute the user-defined command (or Linux command)
        execvp(argv[1], &argv[1]);
        
        // If execvp fails
        perror("execvp failed");
        exit(1);
    } else {
        // Parent process: set an alarm for 5 seconds
        alarm(5);

        // Wait for child to finish (unless it gets killed by the alarm)
        waitpid(child_pid, NULL, 0);
        printf("Parent process finishing.\n");
    }

    return 0;
}
//cc s24.c -o s24
//./s24 sleep 10
*/

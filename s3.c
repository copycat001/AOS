#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to print the file type based on the st_mode field
void print_file_type(struct stat st) {
    if (S_ISREG(st.st_mode)) {
        printf("File Type: Regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("File Type: Character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("File Type: Block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("File Type: FIFO (Named pipe)\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("File Type: Symbolic link\n");
    } else if (S_ISSOCK(st.st_mode)) {
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

    struct stat st;

    // Retrieve file information using stat()
    if (stat(argv[1], &st) == -1) {
        perror("stat failed");
        return 1;
    }

    // Print the inode number and file type
    printf("File Name: %s\n", argv[1]);
    printf("Inode Number: %ld\n", (long) st.st_ino);
    print_file_type(st);

    return 0;
}
//cc s3.c -o s3
//./s3 s3.c
/*
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t child_pid = -1;  // To hold the child's PID

// Signal handler for SIGCHLD (child termination)
void handle_sigchld(int sig) {
    int status;
    // Wait for child process to terminate and get its exit status
    if (child_pid > 0) {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process completed successfully with exit code %d.\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process was terminated by signal %d.\n", WTERMSIG(status));
        }
    }
}

// Signal handler for SIGALRM (timeout)
void handle_sigalrm(int sig) {
    if (child_pid > 0) {
        // If child hasn't completed in time, kill it
        printf("Child process timed out. Terminating child...\n");
        kill(child_pid, SIGKILL);  // Terminate child process
    }
}

int main() {
    // Set up the signal handlers for child termination (SIGCHLD) and timeout (SIGALRM)
    signal(SIGCHLD, handle_sigchld);
    signal(SIGALRM, handle_sigalrm);

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        // If fork failed
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (child_pid == 0) {
        // Child process code
        printf("Child process (PID: %d) is running...\n", getpid());

        // You can replace this with any command or program to be executed by the child
        // For demonstration, we will sleep for 10 seconds, simulating a long-running task
        sleep(10);  // Simulate a long-running task
        printf("Child process completed its task.\n");

        // Exit the child process
        exit(0);
    } else {
        // Parent process code
        printf("Parent process (PID: %d) is waiting for the child to finish...\n", getpid());

        // Set the alarm to go off after 5 seconds
        alarm(5);

        // Parent waits for the child to terminate or timeout
        pause();  // Wait for signals (SIGCHLD or SIGALRM)
    }

    return 0;
}
*/

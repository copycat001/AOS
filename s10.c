#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];  // Array to hold pipe file descriptors: [0] = read, [1] = write
    pid_t pid1, pid2;

    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Fork the first child process (to run "ls")
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed for first child");
        return 1;
    }

    if (pid1 == 0) {  // First child process
        // Close the read end of the pipe since this child will write
        close(pipe_fd[0]);
        
        // Redirect standard output to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);  // File descriptor for stdout is now the write end of the pipe

        // Execute the first command: "ls"
        execlp("ls", "ls", "-l", NULL);  // List files in long format
        // If execlp fails
        perror("execlp failed for ls");
        exit(1);
    }

    // Fork the second child process (to run "grep")
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed for second child");
        return 1;
    }

    if (pid2 == 0) {  // Second child process
        // Close the write end of the pipe since this child will read
        close(pipe_fd[1]);

        // Redirect standard input to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);  // File descriptor for stdin is now the read end of the pipe

        // Execute the second command: "grep"
        execlp("grep", "grep", "txt", NULL);  // Filter files that contain "txt"
        // If execlp fails
        perror("execlp failed for grep");
        exit(1);
    }

    // Parent process
    // Close both ends of the pipe in the parent as they are no longer needed
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both children to finish
    wait(NULL);  // Wait for the first child
    wait(NULL);  // Wait for the second child

    return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];  // Array to hold the two ends of the pipe
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];  // Buffer for reading the message from the pipe

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {  // Error in fork
        perror("fork failed");
        return 1;
    } else if (pid > 0) {  // Parent process
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write a message to the pipe
        printf("Parent process writing to pipe: %s\n", write_msg);
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);

        // Close the write end of the pipe after writing
        close(pipe_fd[1]);
    } else {  // Child process
        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Read from the pipe
        read(pipe_fd[0], read_msg, sizeof(read_msg));
        printf("Child process read from pipe: %s\n", read_msg);

        // Close the read end of the pipe
        close(pipe_fd[0]);
    }

    return 0;
}
*/

#include <stdio.h>

int main() {
    // Open the output file for writing (creates the file if it doesn't exist)
    FILE *file = freopen("output.txt", "w", stdout);
    
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // From here, all printf() will be redirected to "output.txt"
    printf("This will be written to output.txt\n");
    printf("Redirecting standard output to a file is easy!\n");

    // Closing the file (optional, as the program will automatically close it on exit)
    fclose(file);
    
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];  // File descriptors for the pipe
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to run "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1: Executes "ls -l"
        
        // Close the unused read end of the pipe
        close(pipe_fd[0]);
        
        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);  // Close original write end as it's now redirected
        
        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        // If execlp fails
        perror("execlp failed for ls");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to run "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2: Executes "wc -l"
        
        // Close the unused write end of the pipe
        close(pipe_fd[1]);
        
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);  // Close original read end as it's now redirected
        
        // Execute "wc -l"
        execlp("wc", "wc", "-l", NULL);
        // If execlp fails
        perror("execlp failed for wc");
        exit(EXIT_FAILURE);
    }

    // Parent process
    // Close both ends of the pipe as the parent doesn't need to use it
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);  // Wait for child 1 (ls -l) to finish
    waitpid(pid2, NULL, 0);  // Wait for child 2 (wc -l) to finish

    return 0;
}
*/

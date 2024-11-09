#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the output.txt file for writing. Create it if it doesn't exist, and truncate it if it does.
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    // Check if the file was opened successfully
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Duplicate the file descriptor to STDOUT_FILENO (1), which is the standard output.
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 failed");
        close(fd);  // Make sure to close the original file descriptor before returning
        return 1;
    }

    // From this point on, all printf output will be redirected to the file "output.txt"
    printf("This will be written to output.txt\n");
    printf("The standard output has been redirected successfully!\n");

    // Close the file descriptor (optional but good practice)
    close(fd);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];  // Array to hold the two ends of the pipe (pipe_fd[0] for read, pipe_fd[1] for write)

    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();  // Fork the process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {  // Child process
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect standard output to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Close the original write end of the pipe
        close(pipe_fd[1]);

        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    } else {  // Parent process
        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect standard input to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        
        // Close the original read end of the pipe
        close(pipe_fd[0]);

        // Execute "wc -l"
        execlp("wc", "wc", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }

    // Wait for the child process to complete
    wait(NULL);
    return 0;
}
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file for writing (create/overwrite)
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (file == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Redirect stdout to the file using dup2
    if (dup2(file, STDOUT_FILENO) == -1) {
        perror("Failed to redirect stdout");
        close(file);
        return 1;
    }

    // Now, all standard output goes to output.txt
    printf("This message will be written to output.txt instead of the console.\n");

    // Close the file
    close(file);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  // Block Ctrl-C
    sigaddset(&set, SIGQUIT); // Block Ctrl-\
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];  // Pipe file descriptors
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Block signals in the parent process
    block_signals();

    // Fork the first child process to execute "ls -l"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed for ls -l");
        return 1;
    } else if (pid1 == 0) {
        // Child 1: Executes "ls -l"
        close(pipe_fd[0]);  // Close unused read end of the pipe

        // Redirect stdout to pipe write end
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);  // Close the original write end of the pipe

        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed for ls -l");
        exit(1);
    }

    // Fork the second child process to execute "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed for wc -l");
        return 1;
    } else if (pid2 == 0) {
        // Child 2: Executes "wc -l"
        close(pipe_fd[1]);  // Close unused write end of the pipe

        // Redirect stdin to pipe read end
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);  // Close the original read end of the pipe

        // Execute "wc -l"
        execlp("wc", "wc", "-l", NULL);
        perror("execlp failed for wc -l");
        exit(1);
    }

    // Parent process: Close both ends of the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
*/

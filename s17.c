#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char *dir_path = ".";  // Current directory
    int file_count = 0;

    // Open the current directory
    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files in the current directory:\n");

    // Read and check each file in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Print the file name
        printf("%s\n", entry->d_name);
        file_count++;
    }

    // Close the directory
    closedir(dir);

    // Print the total number of files
    printf("\nTotal number of files: %d\n", file_count);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);   // Block Ctrl+C
    sigaddset(&set, SIGQUIT);  // Block Ctrl+\
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Block Ctrl+C and Ctrl+\ signals
    block_signals();

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Fork the first child process to execute "ls -l"
    pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid1 == 0) {
        // First child process: executes "ls -l"
        close(pipe_fd[0]);  // Close unused read end of pipe
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to write end of pipe
        close(pipe_fd[1]);  // Close the original write end of pipe

        execlp("ls", "ls", "-l", NULL);  // Execute "ls -l"
        perror("execlp failed");  // This line is reached only if exec fails
        exit(1);
    }

    // Fork the second child process to execute "wc -l"
    pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid2 == 0) {
        // Second child process: executes "wc -l"
        close(pipe_fd[1]);  // Close unused write end of pipe
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin to read end of pipe
        close(pipe_fd[0]);  // Close the original read end of pipe

        execlp("wc", "wc", "-l", NULL);  // Execute "wc -l"
        perror("execlp failed");  // This line is reached only if exec fails
        exit(1);
    }

    // Parent process: Close both ends of the pipe, wait for children to complete
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to terminate
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
*/

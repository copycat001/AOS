#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

// Function to print file type based on mode
void print_file_type(mode_t mode) {
    if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISREG(mode)) {
        printf("Regular File\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Named Pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown Type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;

    // Iterate through each file passed as a command line argument
    for (int i = 1; i < argc; i++) {
        printf("File: %s\n", argv[i]);

        // Get file status using stat()
        if (stat(argv[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Print the inode number
        printf("Inode Number: %ld\n", (long)file_stat.st_ino);

        // Print the file type
        printf("File Type: ");
        print_file_type(file_stat.st_mode);

        printf("\n");
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipe_fd[2];  // Pipe file descriptors
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Fork the first child process (to run "ls -l")
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed for ls -l");
        return 1;
    } else if (pid1 == 0) {
        // First child process: executes "ls -l"
        close(pipe_fd[0]);  // Close unused read end of pipe

        // Redirect stdout to pipe write end
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);  // Close the original write end of the pipe

        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");  // If exec fails
        exit(1);
    }

    // Fork the second child process (to run "wc -l")
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed for wc -l");
        return 1;
    } else if (pid2 == 0) {
        // Second child process: executes "wc -l"
        close(pipe_fd[1]);  // Close unused write end of pipe

        // Redirect stdin to pipe read end
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);  // Close the original read end of the pipe

        // Execute "wc -l"
        execlp("wc", "wc", "-l", NULL);
        perror("execlp failed");  // If exec fails
        exit(1);
    }

    // Parent process: Close both ends of the pipe and wait for both children to finish
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
*/

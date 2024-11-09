#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];  // Array to hold pipe file descriptors: [0] = read, [1] = write
    pid_t pid;
    
    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Create a child process using fork
    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        // Close the read end of the pipe as the parent will write
        close(pipe_fd[0]);

        // Write data to the pipe
        const char *message = "Hello from parent process!";
        write(pipe_fd[1], message, strlen(message) + 1);  // Including null terminator
        printf("Parent: Written to pipe: %s\n", message);

        // Close the write end after writing
        close(pipe_fd[1]);
    } else {  // Child process
        // Close the write end of the pipe as the child will read
        close(pipe_fd[1]);

        // Read data from the pipe
        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child: Read from pipe: %s\n", buffer);

        // Close the read end after reading
        close(pipe_fd[0]);
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void identify_file_type(const char *path) {
    struct stat file_stat;

    // Get file status
    if (stat(path, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Identify file type based on st_mode field
    printf("File: %s\n", path);
    printf("Type: ");
    
    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("Block Device\n");
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("FIFO or Pipe\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    identify_file_type(argv[1]);

    return 0;
}
*/

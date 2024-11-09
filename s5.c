#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");  // Open the current directory
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    int file_count = 0;

    // Read the directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Ignore the special directories "." and ".."
        if (entry->d_name[0] != '.') {
            printf("File: %s\n", entry->d_name);
            file_count++;
        }
    }

    closedir(dir);  // Close the directory after reading

    printf("\nTotal number of files in current directory: %d\n", file_count);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100  // Define a buffer size for reading messages

int main() {
    int pipe_fd[2];  // File descriptors for the pipe: pipe_fd[0] for read, pipe_fd[1] for write
    pid_t pid;
    char buffer[BUF_SIZE];

    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return EXIT_FAILURE;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Child process
        // Close the read end of the pipe as the child won't read from it
        close(pipe_fd[0]);

        // Write messages to the pipe
        const char* message1 = "Hello World\n";
        const char* message2 = "Hello SPPU\n";
        const char* message3 = "Linux is Funny\n";

        write(pipe_fd[1], message1, strlen(message1));  // Write first message
        write(pipe_fd[1], message2, strlen(message2));  // Write second message
        write(pipe_fd[1], message3, strlen(message3));  // Write third message

        // Close the write end of the pipe after writing
        close(pipe_fd[1]);

        exit(0);  // Exit the child process
    } else {
        // Parent process
        // Close the write end of the pipe as the parent won't write to it
        close(pipe_fd[1]);

        // Read and print messages from the pipe
        printf("Parent process reading from pipe:\n");

        // Read the messages from the pipe
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, BUF_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);  // Print the message to standard output
        }

        // Close the read end of the pipe after reading
        close(pipe_fd[0]);

        // Wait for the child process to finish (optional, to avoid zombie processes)
        wait(NULL);
    }

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char filename[256];
    int file_found = 0;

    // Get the filename from the user
    printf("Enter the filename to search for: ");
    scanf("%s", filename);

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Compare the directory entry with the given filename
        if (strcmp(entry->d_name, filename) == 0) {
            printf("File '%s' is present in the current directory.\n", filename);
            file_found = 1;
            break;
        }
    }

    // If file is not found
    if (!file_found) {
        printf("File '%s' is not present in the current directory.\n", filename);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];  // Pipe file descriptors
    pid_t pid;

    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Fork the child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        close(pipe_fd[0]);  // Close unused read end

        // Messages to be written to the pipe
        char *messages[] = {
            "Hello World\n",
            "Hello SPPU\n",
            "Linux is Funny\n"
        };

        // Write each message to the pipe
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[1], messages[i], strlen(messages[i]));
            sleep(1);  // Sleep to allow parent to read in between writes
        }

        close(pipe_fd[1]);  // Close the write end of the pipe after writing
        exit(0);
    } else {  // Parent process
        close(pipe_fd[1]);  // Close unused write end
        
        char buffer[128];

        // Read and display messages from the pipe
        while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
        }

        close(pipe_fd[0]);  // Close the read end of the pipe after reading
        wait(NULL);  // Wait for the child process to finish
    }

    return 0;
}
*/

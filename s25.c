#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open output.txt for writing
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check for errors opening the file
    if (file == -1) {
        perror("Failed to open output.txt");
        return 1;
    }

    // Redirect stdout to the file using dup2
    if (dup2(file, STDOUT_FILENO) == -1) {
        perror("Failed to redirect stdout");
        close(file);
        return 1;
    }

    // The following printf will now go to output.txt
    printf("This output is redirected to a file.\n");

    // Close the file
    close(file);

    return 0;
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // Open the file "output.txt" in write-only mode, create it if it doesn't exist, and truncate it to zero length
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // Redirect standard output (stdout) to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 failed");
        return 1;
    }

    // Now, all output to stdout will be written to output.txt
    printf("This will be written to the file output.txt instead of the console.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}
*/

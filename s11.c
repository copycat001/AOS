#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rl;
    
    // Get the current limit for the number of open files (RLIMIT_NOFILE)
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Current number of open files limit: %lu\n", rl.rlim_cur);
        printf("Maximum number of open files limit: %lu\n", rl.rlim_max);
    } else {
        perror("getrlimit failed for RLIMIT_NOFILE");
    }

    // Get the current limit for the stack size (RLIMIT_STACK)
    if (getrlimit(RLIMIT_STACK, &rl) == 0) {
        printf("Current stack size limit: %lu\n", rl.rlim_cur);
        printf("Maximum stack size limit: %lu\n", rl.rlim_max);
    } else {
        perror("getrlimit failed for RLIMIT_STACK");
    }

    // Set the resource limit for the number of open files to 1000 (if possible)
    rl.rlim_cur = 1000;
    if (setrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Successfully set the open files limit to 1000.\n");
    } else {
        perror("setrlimit failed for RLIMIT_NOFILE");
    }

    // Set the resource limit for the stack size to 16 MB (if possible)
    rl.rlim_cur = 16 * 1024 * 1024;  // 16 MB
    if (setrlimit(RLIMIT_STACK, &rl) == 0) {
        printf("Successfully set the stack size limit to 16 MB.\n");
    } else {
        perror("setrlimit failed for RLIMIT_STACK");
    }

    // Get the updated limit for the number of open files
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Updated number of open files limit: %lu\n", rl.rlim_cur);
    }

    // Get the updated limit for the stack size
    if (getrlimit(RLIMIT_STACK, &rl) == 0) {
        printf("Updated stack size limit: %lu\n", rl.rlim_cur);
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file output.txt with write permissions, create if it doesn't exist
    int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("open failed");
        return 1;
    }

    // Redirect standard output to the file
    if (dup2(file_fd, STDOUT_FILENO) < 0) {
        perror("dup2 failed");
        close(file_fd);  // Close the file descriptor if dup2 fails
        return 1;
    }

    // Close the original file descriptor since it's now duplicated to STDOUT
    close(file_fd);

    // Write to standard output (will go to output.txt)
    printf("This message will be redirected to output.txt\n");

    return 0;
}
*/

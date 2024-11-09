#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t mode) {
    // File type
    if (S_ISDIR(mode)) printf("d");
    else if (S_ISLNK(mode)) printf("l");
    else if (S_ISREG(mode)) printf("-");

    // Owner permissions
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    // Group permissions
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    // Other permissions
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;

    // Retrieve file information using stat()
    if (stat(argv[1], &st) == -1) {
        perror("stat failed");
        return 1;
    }

    // Print file properties
    printf("File: %s\n", argv[1]);

    // Inode number
    printf("Inode number: %ld\n", (long) st.st_ino);

    // Number of hard links
    printf("Number of hard links: %ld\n", (long) st.st_nlink);

    // File size
    printf("File size: %ld bytes\n", (long) st.st_size);

    // File permissions
    printf("Permissions: ");
    print_permissions(st.st_mode);
    printf("\n");

    // File access time
    printf("Last access time: %s", ctime(&st.st_atime));

    // File modification time
    printf("Last modification time: %s", ctime(&st.st_mtime));

    // File change time (metadata change time)
    printf("Last status change time: %s", ctime(&st.st_ctime));

    return 0;
}
//cc s2.c -o s2
//./s2 s2.c
/*
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int sigint_count = 0;  // Variable to track SIGINT count

// Signal handler for SIGINT
void handle_sigint(int sig) {
    sigint_count++;  // Increment the SIGINT count

    if (sigint_count == 1) {
        // First Ctrl-C: display message and change handler behavior
        printf("Ctrl-C caught for the first time. Press Ctrl-C again to exit.\n");
        
        // Change the signal handler to exit on the next Ctrl-C
        signal(SIGINT, SIG_DFL);  // Set the default behavior (terminate the process)
    } else {
        // Second Ctrl-C: exit the program
        printf("Exiting program after second Ctrl-C.\n");
        exit(0);  // Exit the program
    }
}

int main() {
    // Set up the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    // Keep the program running until Ctrl-C is pressed
    while (1) {
        printf("Program running... Press Ctrl-C to trigger SIGINT.\n");
        sleep(1);  // Sleep to simulate program work and allow signal to be caught
    }

    return 0;
}
*/

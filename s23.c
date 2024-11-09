#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    char filename[256];
    struct dirent *entry;
    DIR *dp;

    // Get the filename to search for
    printf("Enter the filename to check: ");
    scanf("%s", filename);

    // Open the current directory
    dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    // Iterate through the directory entries
    int found = 0;  // Flag to indicate whether the file was found
    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            // If file name matches, set found flag to 1
            found = 1;
            break;
        }
    }

    // Close the directory
    closedir(dp);

    // Output the result
    if (found) {
        printf("File '%s' found in the current directory.\n", filename);
    } else {
        printf("File '%s' not found in the current directory.\n", filename);
    }

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void file_type(struct stat st) {
    // Check the file type using the st_mode field
    if (S_ISREG(st.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("FIFO (Named pipe)\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown file type\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;

    // Get file status using stat()
    if (stat(argv[1], &st) == -1) {
        perror("stat failed");
        return 1;
    }

    // Display the file type
    file_type(st);

    return 0;
}
*/

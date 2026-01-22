#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 4096
#define BUFFER_SIZE 1024

/**
 * Searches for the 'target' string within a specific file.
 * Prints the file path if the string is found.
 */
void search_file(const char *filepath, const char *target) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        // Silently skip files we cannot open (e.g., permission denied)
        return;
    }

    char buffer[BUFFER_SIZE];
    int line_num = 1;
    int found = 0;

    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, target) != NULL) {
            if (!found) {
                printf("\n[MATCH] File: %s\n", filepath);
                found = 1; // Mark found to avoid printing filename multiple times
            }
            // Optional: Print the line number and content where it was found
            // Remove newline for cleaner output
            buffer[strcspn(buffer, "\n")] = 0; 
            printf("  -> Line %d: %s\n", line_num, buffer);
        }
        line_num++;
    }

    fclose(fp);
}

/**
 * Recursively traverses directories to find files.
 */
void search_directory(const char *base_path, const char *target) {
    DIR *dir;
    struct dirent *entry;
    char path[MAX_PATH_LENGTH];

    // Open the directory
    if (!(dir = opendir(base_path))) {
        // Could not open directory (likely permission denied), just return
        return;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip special directories "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Construct the full path
        // snprintf is used to prevent buffer overflows
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        struct stat path_stat;
        // lstat is used to check if it is a directory or file
        if (lstat(path, &path_stat) == -1) {
            continue;
        }

        // Check if it is a directory
        if (S_ISDIR(path_stat.st_mode)) {
            // Recursive call
            search_directory(path, target);
        } 
        // Check if it is a regular file
        else if (S_ISREG(path_stat.st_mode)) {
            search_file(path, target);
        }
    }
    closedir(dir);
}

int main() {
    char target[BUFFER_SIZE];
    char path[MAX_PATH_LENGTH];

    // User Inputs as requested
    printf("Type here which you want to find: ");
    if (fgets(target, sizeof(target), stdin) != NULL) {
        // Remove the newline character from input
        target[strcspn(target, "\n")] = 0;
    }

    printf("Type here path: ");
    if (fgets(path, sizeof(path), stdin) != NULL) {
        // Remove the newline character from input
        path[strcspn(path, "\n")] = 0;
    }

    printf("\n--- Searching for '%s' in '%s' ---\n", target, path);
    
    // Start the search
    search_directory(path, target);

    printf("\n--- Search Complete ---\n");

    return 0;
}

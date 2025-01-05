#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024 // Define the buffer size for reading and writing data

// Function to create and write to a file
void create_and_write_file(const char *filename, const char *content) {
    // Open the file for writing; create it if it doesn't exist, truncate it if it does
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { // Check for errors while opening the file
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    // Write the content to the file
    if (write(fd, content, strlen(content)) == -1) {
        perror("Error writing to file");
        close(fd); // Close the file descriptor before exiting
        exit(EXIT_FAILURE);
    }

    printf("File '%s' created and written successfully.\n", filename);
    close(fd); // Close the file descriptor
}

// Function to read and display the content of a file
void read_file(const char *filename) {
    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { // Check for errors while opening the file
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE]; // Buffer to hold the data being read
    ssize_t bytes_read; // Number of bytes read from the file

    printf("Content of '%s':\n", filename);
    // Read the file in chunks until the end is reached
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Write the read data to standard output
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("Error displaying file content");
            close(fd); // Close the file descriptor before exiting
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) { // Check for errors during reading
        perror("Error reading file");
    }

    close(fd); // Close the file descriptor
}

// Function to copy a file
void copy_file(const char *source, const char *destination) {
    // Open the source file for reading
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) { // Check for errors while opening the source file
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open or create the destination file for writing
    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) { // Check for errors while opening the destination file
        perror("Error creating destination file");
        close(src_fd); // Close the source file descriptor before exiting
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE]; // Buffer to hold the data being copied
    ssize_t bytes_read; // Number of bytes read from the source file

    // Read from the source and write to the destination in chunks
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) == -1) { // Check for errors during writing
            perror("Error writing to destination file");
            close(src_fd); // Close both file descriptors before exiting
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) { // Check for errors during reading
        perror("Error reading source file");
    }

    printf("File '%s' copied to '%s' successfully.\n", source, destination);

    close(src_fd); // Close the source file descriptor
    close(dest_fd); // Close the destination file descriptor
}

int main() {
    const char *file1 = "example.txt"; // Name of the first file to create and write to
    const char *file2 = "copy_example.txt"; // Name of the copied file
    const char *content = "Hello, this is a demonstration of file operations in C.\n"; // Content to write to the file

    // Create and write to a file
    create_and_write_file(file1, content);

    // Read the created file
    read_file(file1);

    // Copy the file
    copy_file(file1, file2);

    // Read the copied file
    read_file(file2);

    return 0; // Exit the program successfully
}

// pipe_example.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent through pipe";
    char read_msg[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(fd[0]);  // Close read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);  // Close write end
        wait(NULL);
    }
    else {  // Child process
        close(fd[1]);  // Close write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);  // Close read end
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        // Display prompt
        printf("#cisfun$ ");
        fflush(stdout);

        // Read command
        if (!fgets(command, sizeof(command), stdin))
        {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            // Execute the command
            if (execve(command, NULL, NULL) == -1)
            {
                // Handle command not found
                perror("Command not found");
                exit(EXIT_FAILURE);
            }
        }
        else // Parent process
        {
            // Wait for the child process to finish
            wait(NULL);
        }
    }

    return 0;
}


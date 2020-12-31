#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "my_system.h"

void my_system(char *chaine)
{
    char *const arguments[] = {"sh", "-c", chaine, NULL};
    int pid, etat;
    pid = fork();
    if (pid == -1)
        perror("fork");
    else if (pid == 0)
    {
        execv("/bin/sh", arguments);
        printf("Ce ligne ne devrait être exécuté\n");
    }
    else if (pid > 0)
    {
        wait(&etat);
    }
}

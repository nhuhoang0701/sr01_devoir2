#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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

int premier(int nb)
{
    int r = 0;

    for (int i = 1; i <= nb; i++)
    {
        if (nb % i == 0)
        {
            r++;
        }
    }
    return (r > 2) ? 0 : 1;
}

void explorer(int debut, int fin)
{
    int etat, pid, pid2;
    pid = fork();
    if (pid == 0)
    {
        for (int i = debut; i <= fin; i++)
        {

            if (premier(i) == 1)
            {
                pid2 = fork();
                if (pid2 == 0)
                {
                    char chaine[1000];
                    sprintf(chaine, "echo '%d est un nombre premier, écrit par le processus %d. "
                                    "Son père est le processus %d.\n\tLe processus qui a écrit le "
                                    "message sur le terminal est' $$>>nbr_premiers_2.txt",
                            i, getpid(), getppid());
                    my_system(chaine);
                    sleep(2);
                    exit(0);
                }
                else
                {
                    wait(&etat); // instruction 41
                }
            }
        }
        exit(0);
    }
    else
    {
        wait(&etat); // instruction 46
    }
}

int main()
{
    int grp = 1;
    while (grp <= 11)
    {
        explorer(grp + 1, grp + 10);
        grp = grp + 10;
    }
}

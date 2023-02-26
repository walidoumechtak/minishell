#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{

    (void) ac;
    (void) av;

    char *path = "/bin/cat";
    char *cmd = "cat";
    char *arg = "-e";
    char *arg2 = "main.c";
    char *cmds[] = {cmd, arg, NULL, NULL};

    execve(path, cmds, env);
}
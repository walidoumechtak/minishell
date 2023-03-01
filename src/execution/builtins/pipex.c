
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	fd[2];
	int i;

	i = 0;
	av[1] = "/bin/ls";
	av[2] = "/usr/bin/wc";
	av[3] = "/usr/bin/wc";
	av[4] = "/bin/ls";
	av[5] = NULL;

	dup2(0, 0);
	while (av[i])
	{
		char *args[] = {av[i], NULL};
		pipe(fd);
		int pid1 = fork();
		if (pid1 == 0)
		{
			if (av [i + 1] != NULL)
				dup2(fd[1], STDOUT_FILENO);
			else
				dup2(1, 1);
			close(fd[1]);
			close(fd[0]);
			execve(av[i], args, NULL);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		i++;
	}
	wait(NULL);
	return (0);
}

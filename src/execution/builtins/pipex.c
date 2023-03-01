
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	fd[2];
	int i;

	i = 1;
	av[1] = "/bin/ls";
	av[2] = "/bin/ls";
	av[3] = "/bin/ls";
	av[4] = "/usr/bin/echo";
	av[5] = NULL;

	pipe(fd);
	while (av[i + 1])
	{
		i++;
		int pid1 = fork();
		if (pid1 == 0)
		{
			char *args[] = {av[i], NULL};
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(av[i], args, NULL);
		}
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	char *args[] = {av[i], "hamza", NULL};
	execve(av[i], args, NULL);
	return (0);
}

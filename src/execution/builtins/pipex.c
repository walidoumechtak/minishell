
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	fd[2];
	int i;

	i = 1;
	av[1] = "/bin/ls";
	av[3] = NULL;
	int pid0 = fork();
	if (pid0 == 0)
	{
		while (av[i + 1] || av[i + 1][0])
		{

			
			pipe(fd); 
			int pid1 = fork();
			if (pid1 < 0)
				return (-1);
			if (pid1 == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				execve(av[i], NULL, NULL);
			}
			wait(NULL);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			i++;
		}
	}
	wait(NULL);
	close(fd[0]);
	close(fd[1]);
	execve(av[i], NULL, NULL);

	return (0);
}

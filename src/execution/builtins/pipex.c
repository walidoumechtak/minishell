
#include "minishell.h"

int	main(int ac, char **argv)
{
	int	fd[2];
	int i;

	i = 0;
	/*				 cmd1      arg   	 |     cmd2         agrs             */
	char *av[] = {"/bin/cat", "ft_echo.c", "/bin/echo", "Hello world", NULL};
	ac = 5;

	if (ac == 1)
		return (0);
	/* The files descriptor you wand to read and write on it*/
	int infile = STDIN_FILENO;
	int outfile = STDOUT_FILENO;
	/* Duplicate the file descriptor you want to read from*/
	dup2(infile, STDIN_FILENO);
	while (av[i])
	{
		char *args[] = {av[i], av[i + 1], NULL};
		/*Create a pip*/
		pipe(fd);
		/*Fork To exeute the command*/
		int pid1 = fork();
		if (pid1 == 0) /*this is The  child process*/
		{
			if (av[i + 2] != NULL) /*if the the is a pipe you need the write to it*/
				dup2(fd[1], STDOUT_FILENO);
			else /*If it is the last command in pipe you need to wirte in STDOUT*/
				dup2(outfile, 1);
			close(fd[1]);
			close(fd[0]);
			execve(av[i], args, NULL);
		}
		 /*The parent process*/
			/* Duplicate the file descriptor you want to read from*/
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			i = i + 2;
	}
	wait(NULL);
	return (0);
}

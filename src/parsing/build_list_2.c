#include "minishell.h"

void    free_and_shift(char **arr, int i)
{
    int j;
    int temp;
    int sim_i;

    temp = 0;
    while (arr[temp])
        temp++;
    free(arr[i]);
    free(arr[i + 1]);
    arr[i] = NULL;
    arr[i + 1] = NULL;
    j = 0;
    sim_i = i;
    while (j < 2)
    {
        i = sim_i;
        while (i < temp)
        {
            arr[i] = arr[i + 1];
            i++;
        }
        j++;
    }
}
/*=====================================================================================================================*/

void    open_file(t_minishell *ptr, char **arr, int mode, int i)
{
    if (mode == 1)
    {
        ptr->o_file->fd = open(arr[i + 1], O_RDONLY);
        ptr->o_file->file = ft_strdup(arr[i + 1]);
        ptr->o_file->mode = 1;
        free_and_shift(arr, i);
    }
    else if (mode == 2)
    {
        ptr->o_file->file = ft_strdup(arr[i + 1]);
        ptr->o_file->mode = 2;
        free_and_shift(arr, i);
    }
    else if (mode == 3)
    {
        ptr->o_file->file = ft_strdup(arr[i + 1]);
        ptr->o_file->mode = 3;
        free_and_shift(arr, i);
    }
    
}
/*=====================================================================================================================*/


void    signal_handler2(int sig)
{
    (void) sig;
    //printf("---> %d \n", sig);
    //printf("recieved signal child...\n");
    exit(9);
}

/**
 * open_ex_heredoc - open heredoc and any $USER should be expainded
*/

int    open_heredoc(t_minishell *ptr, char **arr, int i, int is_exp)
{
    // struct sigaction action;
    static int  rand;
    char    *char_rand;
    char    *file;
    char    *str;
    int e_s;
    int fd[2];
    int fd_file;
    int    c;
    pid_t pid;

    // action.sa_handler = signal_handler1;
    // sigemptyset(&action.sa_mask);
    // action.sa_flags = 0;
    // sigaction(SIGINT, &action, NULL);
    if (pipe(fd) < 0)
        return (-1);
    char_rand = ft_itoa(rand);
    file = ft_strjoin("/tmp/here_file", char_rand);
    while (access(file, F_OK) == 0)
    {
        free(file);
        free(char_rand);
        char_rand = ft_itoa(rand++);
        file = ft_strjoin("/tmp/here_file", char_rand);
    }
    free(char_rand);
    pid = fork();
    if (pid < 0)
        return (-2);
    if (pid == 0)
    {
        signal(SIGINT, signal_handler2);
        close(fd[0]);
        fd_file = open(file, O_RDWR | O_CREAT, 0777);
        str = get_next_line(0);
        while (str != NULL)
        {
            if (ft_strncmp(str, arr[i + 1], ft_strlen(str) - 1) == 0 && ft_strlen(str) > 1)
                break ;
            if (is_exp == 0)
                expaind_heredoc(ptr, &str);
            ft_putstr_fd(str, fd_file);
            free(str);
            str = get_next_line(0);
        }
        write(fd[1], &fd_file, sizeof(int));
        close(fd[1]);
        exit (0);
    }
    else
    {
        close(fd[1]);
        read(fd[0], &c, sizeof(int));
        ptr->o_file->file = file;
        ptr->o_file->fd = c;
        ptr->o_file->mode = 4;
        close(fd[0]);
        free_and_shift(arr, i);
        // wait(&e_s);
        waitpid(pid, &e_s, 0);
        if (WEXITSTATUS(e_s) == 9)
        {
            ptr->signal_stop = -9;
            printf("signal_stop %d\n", ptr->signal_stop);
            return (0);
        }
    }
    rand++;
    return (0);
}
/*=====================================================================================================================*/
int open_rederiction(t_minishell *ptr, t_list **old_node, t_cmd **new_cmd)
{
    t_list  *old;
    t_list  *new;
    t_cmd *new_c;
    
    t_cmd_v1    *skin;
    int i;
    int k;
    int l;
    //int j;

    i = 0;
    new_c = *new_cmd;
    old = *old_node;
    skin = (t_cmd_v1 *)old->content;
    new_c->opened_files = NULL;
    k = 0;
    l = 0;
    while (((t_cmd_v1 *)old->content)->cmd[i] && skin->cmd[i][0] != '\0')
    {
        if (ft_strncmp(skin->cmd[i], ">", ft_strlen(skin->cmd[i])) == 0 && skin->flags_red[k++] == 1)
        {
            ptr->o_file = malloc(sizeof(t_open_file));
            open_file(ptr, skin->cmd, 2, i);
        }
        else if (ft_strncmp(skin->cmd[i], "<", ft_strlen(skin->cmd[i])) == 0 && skin->flags_red[k++] == 1)
        {
            ptr->o_file = malloc(sizeof(t_open_file));
            open_file(ptr, skin->cmd, 1, i);
        }
        else if (ft_strncmp(skin->cmd[i], "<<", ft_strlen(skin->cmd[i])) == 0 && skin->flags_red[k++] == 1)
        {
            ptr->o_file = malloc(sizeof(t_open_file));
            if (skin->expaind_here[l] == 1)
            {
                ptr->o_file->fd = 0;
                open_heredoc(ptr, skin->cmd, i, 0);
                l++;
            }
            else
            {
                ptr->o_file->fd = 0;
                open_heredoc(ptr, skin->cmd, i, 404);
            }
        }
        else if (ft_strncmp(skin->cmd[i], ">>", ft_strlen(skin->cmd[i])) == 0 && skin->flags_red[k++] == 1)
        {
            ptr->o_file = malloc(sizeof(t_open_file));
            open_file(ptr, skin->cmd, 3, i);
        }
        else if (skin->cmd == NULL)
            break ;
        else
        {
            i++;
            ptr->o_file = NULL;
        }
        if (ptr->o_file != NULL && skin->cmd != NULL) // create linked list of redrections < > << >>
        {
            new = ft_lstnew(ptr->o_file);
            if (!new)
                return (-1);
            ft_lstadd_back(&new_c->opened_files, new);
        }
    }
    return (0);
}

/*
	modes :
	1 --> infile
	2 --> outfile
	3 --> append
	4 --> heredoc
*/

/*=====================================================================================================================*/

/**
* build_list_2 - building the final linked list that should be sned to execute part 
* we loop throw a linked list of file and their file descriptor and assigne to each node 
* hes **cmd and in_fd and out_fd
*/

int build_list_2(t_minishell *ptr)
{
    t_list *temp;
    t_list *new;
    int state;
    int i;

    i = 0;
    ptr->signal_stop = 0;
    temp = ptr->list_v1;
    ptr->list_cmd = NULL;
    while (temp)
    {
        ptr->cmd = malloc(sizeof(t_cmd));
        ptr->cmd->fd_in = 0;
        ptr->cmd->fd_out = 1;
        state = open_rederiction(ptr, &temp, &ptr->cmd);
        if (state != 0)
            return (state);
        if (ptr->signal_stop == -9)
            return (-9);
        if (state != 0)
            return (state);
        ptr->cmd->cmd = ((t_cmd_v1 *)temp->content)->cmd;
        new = ft_lstnew(ptr->cmd);
        if (!new)
            return (-1);
        ft_lstadd_back(&ptr->list_cmd, new);
        temp = temp->next;
    }
    return (0);
}
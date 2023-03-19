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



/**
 * open_ex_heredoc - open heredoc and any $USER should be expainded
*/

int    open_heredoc(t_minishell *ptr, char **arr, int i, int is_exp)
{
    char **split;
    static int  rand;
    char    *char_rand;
    char    *file;
    char    *str;
    int fd[2];
    int fd_file;
    int    c;
    int pid;

    if (pipe(fd) < 0)
        return (-1);
    is_exp = 0;
    char_rand = ft_itoa(rand);
    file = ft_strjoin("here_file", char_rand);
    while (access(file, F_OK) == 0)
    {
        free(file);
        free(char_rand);
        char_rand = ft_itoa(rand++);
        file = ft_strjoin("here_file", char_rand);
    }
    free(char_rand);
    pid = fork();
    if (pid < 0)
        return (-2);
    if (pid == 0)
    {
        close(fd[0]);
        fd_file = open(file, O_RDWR | O_CREAT, 0777);
        // str = get_next_line(0);
        while (1)
        {
            str = get_next_line(0);
            if (str == NULL)
            {
                break ;
            }
            split = ft_split(str, '\n');
            if (ft_strncmp(str, arr[i + 1], ft_strlen(split[0])) == 0)
                break ;
            // if (is_exp == 0)
            //     expaind_heredoc(ptr, &str);
            ft_putstr_fd(split[0], fd_file);
            free(str);
            free_spilte(split);
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
        wait(NULL);
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
                 open_heredoc(ptr, skin->cmd, i, 404);
        }
        else if (ft_strncmp(skin->cmd[i], ">>", ft_strlen(skin->cmd[i])) == 0 && skin->flags_red[k++] == 1)
        {
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

// void    free_opened_files(t_minishell *ptr)
// {
//     t_open_file *link;
//     t_list  *temp;
//     temp = ptr->opened_files;
//     while (temp)
//     {
//         if (((t_open_file *)temp->content)->mode != 4)
//         {
//             link = ((t_open_file *)temp->content);
//             free(link->file);
//         }
//         temp = temp->next;
//     }
//     ft_lstclear(&ptr->opened_files, del);
// }
/*=====================================================================================================================*/

/**
* build_list_2 - building the final linked list that should be sned to execute part 
* we loop throw a linked list of file and their file descriptor and assigne to each node 
* hes **cmd and in_fd and out_fd
*/

int build_list_2(t_minishell *ptr)
{
    // (void)ptr;
    t_list *temp;
    t_list *new;
    
    // t_list *temp_files;
    int state;
    int i;
    int j;

    i = 0;
    j = 0;
    temp = ptr->list_v1;
    ptr->list_cmd = NULL;
    while (temp)
    {
        ptr->cmd = malloc(sizeof(t_cmd));
        ptr->cmd->fd_in = 0;
        ptr->cmd->fd_out = 1;
        state = open_rederiction(ptr, &temp, &ptr->cmd);
        // temp_files = ptr->opened_files;
        // if (state != 0) 
        //      return (state);
        // while (temp_files) // loop throw the linked list that containe file and in_fd and out_fd !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // {
        //     if (((t_open_file *)temp_files->content)->mode == 1)
        //     {
        //         if (((t_open_file *)temp_files->content)->fd < 0)
        //         {
        //             open_error(ptr, ((t_open_file *)temp_files->content)->file,": no such file or directory\n", 1);
        //             //return (3);
        //         }
        //         // if (cmd->fd_in != 0)
        //         // {
        //         //     printf("fd_int != 0\n");
        //         //     close(cmd->fd_in);
        //         // }
        //         cmd->fd_in = ((t_open_file *)temp_files->content)->fd;
        //     }//--------------------------------------------------------------
        //     else if (((t_open_file *)temp_files->content)->mode == 4)
        //     {
        //         printf("in_fd   ==>> %d\n", ((t_open_file *)temp_files->content)->fd);
        //         if (((t_open_file *)temp_files->content)->fd < 0)
        //         {
        //             open_error(ptr, NULL,"failed to open heredoc\n", 1);
        //             //return (3);
        //         }
        //         // if (cmd->fd_in != 0)
        //         // {
        //         //     printf("fd_int != 0\n");
        //         //     close(cmd->fd_in);
        //         // }
        //         cmd->fd_in = ((t_open_file *)temp_files->content)->fd;
        //     }//--------------------------------------------------------------
        //     // else if (((t_open_file *)temp_files->content)->mode == 2)
        //     // {
        //     //     if (((t_open_file *)temp_files->content)->fd < 0)
        //     //     {
        //     //         open_error(ptr, ((t_open_file *)temp_files->content)->file,": Permission denied\n", 1);
        //     //         //return (3);
        //     //     }
        //     //     // if (cmd->fd_out != 1)
        //     //     // {
        //     //     //     printf("fd_out != 1\n");
        //     //     //     close(cmd->fd_out);
        //     //     // }
        //     //     cmd->fd_out = ((t_open_file *)temp_files->content)->fd;
        //     // }//--------------------------------------------------------------
        //     // else if (((t_open_file *)temp_files->content)->mode == 3)
        //     // {
        //     //     if (((t_open_file *)temp_files->content)->fd < 0)
        //     //     {
        //     //         open_error(ptr, ((t_open_file *)temp_files->content)->file,": Permission denied\n", 1);
        //     //         //return (3);
        //     //     }
        //     //     if (cmd->fd_out != 1)
        //     //     {
        //     //         printf("fd_out != 1\n");
        //     //         close(cmd->fd_out);
        //     //     }
        //     //     cmd->fd_out = ((t_open_file *)temp_files->content)->fd;
        //     // }//--------------------------------------------------------------  
        //     temp_files = temp_files->next;
        // }                                      // =============================== end of looop !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ptr->cmd->cmd = ((t_cmd_v1 *)temp->content)->cmd;
        //j = 0;
        // while (((t_cmd_v1 *)temp->content)->cmd[j])
        //     printf("new cmd %s\n", ((t_cmd_v1 *)temp->content)->cmd[j++]);
        new = ft_lstnew(ptr->cmd);
        if (!new)
            return (-1);
        ft_lstadd_back(&ptr->list_cmd, new);
        //ptr->out_access = 0;
        // free_opened_files(ptr);
        temp = temp->next;
    }
    return (0);
}
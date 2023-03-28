#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libft/inc/libft.h"
 #include <strings.h>
#include <fcntl.h>
#include <signal.h>


int main()
{
    char *str = "      time | echo walid";
    char    *new = ft_strtrim(str, "time");
    printf("the new string : -%s-\n", new);
    return 0;
}

// int main(void)
// {
//     t_list  *head;
//     t_node  *no;
    
//     head = NULL;
//     int i = 0;
//     while (i < 10)
//     {
//         no = (t_node *)malloc(sizeof(t_node));
//         no->i_pipe = i;
//         ft_lstadd_back(&head,ft_lstnew(no));
//         i++;
//     }

//     for (size_t i = 0; head; i++)
//     {
//         printf("%d\n", ((t_node *)head->content)->i_pipe);
//         head = head->next;
//     }
// }

//int main()
//{
    // char *cmd[] = {"alias", "ccc=clear", NULL};
    // char *path = "/usr/bin/alias";

    // execve(path, cmd, NULL);

//}
// int main()
// {
    // char *str = "walid@111@";
    // printf("%s\n", ft_substr(str, 0, 2));
    // int fd = open("/dev/ttys000", O_RDWR | O_CREAT, 0777);
    // printf("fd is : %d\n", fd);
    // char *cmd[] = {"/", "lll", "main.c", NULL};
    // execve("/bin/", cmd , NULL);
    // int *arr = ft_calloc(3 , sizeof(int));
    // printf("%d\n", arr[0]);
    // printf("%d\n", arr[1]);
    // printf("%d\n", arr[2]);

// }

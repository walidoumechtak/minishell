#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libft/inc/libft.h"
 #include <strings.h>

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

int main()
{
    char *str = "@walid@";
    printf("%s\n", ft_substr(str, 1, 5));
}

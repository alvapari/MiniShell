#include "../include/minishell.h"

void ft_pwd(t_cmd *cmd)
{
    char *dir;

    dir = malloc(sizeof(char)* 1024);
    getcwd(dir, 1024);
    printf("%s\n", dir);
    free(dir);
    builtin_end(cmd->data, 0);
}
/* #include "../incs/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void    print_cmd_list(t_cmd *cmds)
{
    t_cmd   *cmd;
    t_redir *redir;
    int     i;
    int     cmd_num;

    cmd = cmds;
    cmd_num = 1;
    while (cmd)
    {
        printf("--- CMD %d ---\n", cmd_num++);
        i = 0;
        while (cmd->args && cmd->args[i])
        {
            printf("  arg[%d]: %s\n", i, cmd->args[i]);
            i++;
        }
        redir = cmd->redirs;
        while (redir)
        {
            printf("  redir type: %d -> %s\n", redir->type, redir->file);
            redir = redir->next;
        }
        cmd = cmd->next;
    }
}

int    main(void)
{
    char    *line;
    t_token *tokens;
    t_cmd   *cmds;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break ;
        if (*line == '\0')
        {
            free(line);
            continue ;
        }
        add_history(line);
        tokens = ft_tokenization_handler(line);
        free(line);
        if (!tokens)
            continue ;
        cmds = ft_parse(tokens);
        ft_clear_token_list(&tokens);
        if (!cmds)
            continue ;
        print_cmd_list(cmds);
        ft_free_cmd_list(&cmds);
    }
    return (0);
} */

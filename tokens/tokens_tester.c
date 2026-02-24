#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tokens.h"

const char *token_type_to_str(t_token_type type)
{
    if (type == T_IDENTIFIER) return "IDENTIFIER";
    if (type == T_PIPE)       return "PIPE";
    if (type == T_LESS)       return "LESS";
    if (type == T_GREAT)      return "GREAT";
    if (type == T_DLESS)      return "DLESS";
    if (type == T_DGREAT)     return "DGREAT";
    if (type == T_EOF)        return "EOF";
    return "UNKNOWN";
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("Token: %-10s", token_type_to_str(tokens->type));
        if (tokens->value)
            printf(" | value: \"%s\"", tokens->value);
        printf("\n");
        tokens = tokens->next;
    }
}

int main(void)
{
    char    *line;
    t_token *tokens;

    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;

        if (*line)
            add_history(line);

        tokens = ft_tokenization_handler(line);
        if (!tokens)
        {
            printf("Lexer error\n");
            free(line);
            continue;
        }

        print_tokens(tokens);
        ft_clear_token_list(&tokens);
        free(line);
    }
    return (0);
}

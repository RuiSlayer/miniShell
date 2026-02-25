/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:35:32 by fgameiro          #+#    #+#             */
/*   Updated: 2026/02/25 01:51:44 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int  ft_add_arg(t_cmd *cmd, char *value)
{
    int     count;
    char    **new_args;

    count = 0;
    while (cmd->args && cmd->args[count])
        count++;
    new_args = ft_realloc(cmd->args, sizeof(char *) * (count + 2));
    if (!new_args)
        return (0);
    new_args[count] = ft_strdup(value);
    new_args[count + 1] = NULL;
    cmd->args = new_args;
    return (1);
}

static int  ft_add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
    t_redir *new;
    t_redir *curr;

    new = ft_calloc(1, sizeof(t_redir));
    if (!new)
        return (0);
    new->type = type;
    new->file = ft_strdup(file);
    if (!cmd->redirs)
        cmd->redirs = new;
    else
    {
        curr = cmd->redirs;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
    return(1);
}
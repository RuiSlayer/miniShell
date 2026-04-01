/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:38:51 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/01 23:07:53 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "tokens.h"

typedef enum e_redir_type
{
    R_IN,       // 
    R_OUT,      // >
    R_HEREDOC,  // 
    R_APPEND    // >>
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;
    char            *file;      // filename or heredoc delimiter
    struct s_redir  *next;
    int heredoc_fd;
}   t_redir;

typedef struct s_cmd
{
    char            **args;// NULL-terminated array: args[0] = command name
    t_redir         *redirs;// linked list of redirections
    struct s_cmd    *next;// next command in pipeline
}   t_cmd;

//FREE MEMORY
void    ft_free_redir_list(t_redir *redir);//free the list of redirections */
void	ft_free_cmd_list(t_cmd **lst);//free the cmd struct

//PARSE
t_cmd   *ft_parse(t_token *tokens);
t_cmd   *ft_parse_pipeline(t_token **tok);
t_cmd   *ft_parse_command(t_token **tok);

//BUILD
int     ft_add_arg(t_cmd *cmd, char *value);
int     ft_add_redir(t_cmd *cmd, t_redir_type type, char *file);

//TESTING
void	print_cmd_list(t_cmd *cmds);
#endif
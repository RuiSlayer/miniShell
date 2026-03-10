/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:38:51 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/10 12:24:42 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdbool.h>//booleans
# include <stdio.h>//printf
# include <stdlib.h>
# include <stddef.h>
# include "42libft/libft.h"
# include "tokens/tokens.h"

//Error messages
# define ERR_SYNTAX_PIPE "syntax error near unexpected token `|'"
# define ERR_SYNTAX_REDIR "syntax error near unexpected token `newline'"
# define ERR_SYNTAX_TOKEN "syntax error near unexpected token"
# define ERR_MALLOC "minishell: memory allocation failed"

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
}   t_redir;

typedef struct s_cmd
{
    char            **args;// NULL-terminated array: args[0] = command name
    t_redir         *redirs;// linked list of redirections
    struct s_cmd    *next;// next command in pipeline
}   t_cmd;

//FREE MEMORY
/* void	ft_free_redir_list(t_redir *redir);//free the list of redirections */
void	ft_free_cmd_list(t_cmd **lst);//free the cmd struct

#endif PARSER_H
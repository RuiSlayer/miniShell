/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:38:51 by fgameiro          #+#    #+#             */
/*   Updated: 2026/02/24 21:39:56 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    char            **args;     // NULL-terminated array: args[0] = command name
    t_redir         *redirs;    // linked list of redirections
    struct s_cmd    *next;      // next command in pipeline
}   t_cmd;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:38:51 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/17 23:33:30 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "errors.h"

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
	int				heredoc_fd;
	char			*herefile;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	bool			*args_quoted;
	bool			is_empty;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

void			ft_free_redir_list(t_redir *redir);
void			ft_free_cmd_list(t_cmd **lst);
t_cmd			*ft_parse(t_token *tokens);
t_cmd			*ft_parse_pipeline(t_token **tok);
t_cmd			*ft_parse_command(t_token **tok);
int				ft_add_arg(t_cmd *cmd, char *value, bool is_quoted);
int				ft_add_redir(t_cmd *cmd, t_redir_type type, char *file);
int				else_branch_parse(t_token **tok, t_cmd	*cmd);
t_redir_type	ft_redir_type(t_token *tok);
char			*ft_token_to_str(t_token_type type);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/03/25 00:31:00 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISELL_EXEC_H
# define MINISELL_EXEC_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/chardefs.h>
# include "parser.h"
# include "shell.h"
# include "expansion.h"
# include "tokens.h"


int		echo_cmd_std(char *line);
int		echo_cmd_redir(char *line);
int		pwd(void);
int		built_export(t_cmd *cmds, t_env **env);
int		unset(t_cmd *cmds, t_env **env);
int		print_env(t_env *env);
int		cd(t_cmd *cmds, t_env **env);
void	setup_signals(void);



#endif
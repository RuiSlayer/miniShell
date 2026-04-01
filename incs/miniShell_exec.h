/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/04/01 01:03:37 by rucosta          ###   ########.fr       */
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
# include <sys/wait.h>
# include <linux/limits.h>
# include "parser.h"
# include "shell.h"
# include "expansion.h"
# include "tokens.h"

//int		echo_cmd_std(char *line);
//int		echo_cmd_redir(char *line);
int		echo(t_cmd	*cmd);
int		pwd(void);
int		built_export(t_cmd *cmds, t_env **env);
int		unset(t_cmd *cmds, t_env **env);
int		print_env(t_env *env);
int		cd(t_cmd *cmds, t_env **env);
void	setup_signals(void);
char	*ft_find_path(char *cmd, t_env *env);
void	ft_free_split(char **split);


#endif
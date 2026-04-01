/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/04/01 22:06:26 by rucosta          ###   ########.fr       */
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

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*cmd;
	pid_t	last_pid;
}	t_pipe;

int		echo(t_cmd	*cmd);
int		pwd(void);
int		built_export(t_cmd *cmds, t_env **env);
int		unset(t_cmd *cmds, t_env **env);
int		print_env(t_env *env);
int		cd(t_cmd *cmds, t_env **env);
void	setup_signals(void);
char	*ft_find_path(char *cmd, t_env *env);
void	ft_free_split(char **split);
void	execute_pipeline(t_shell *shell);
int		external_cmds(t_shell *shell);
int		run_builtin(t_shell *shell);
int		is_builtin(t_shell *shell);
void	run_builtin_in_parent(t_cmd *cmd, t_shell *shell);
int		apply_redirects(t_redir *redir);


#endif
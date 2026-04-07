/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/04/07 05:38:53 by rucosta          ###   ########.fr       */
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
#include <sys/stat.h>
# include <linux/limits.h>
# include "expansion.h"
# include "shell.h"

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
void	ft_free_double_pointer(char **split);
void	execute_pipeline(t_shell *shell);
void	external_cmds(t_shell *shell);
void	run_builtin(t_shell *shell);
int		is_builtin(t_shell *shell);
void	run_builtin_in_parent(t_pipe *pipe_s, t_shell *shell);
int		apply_redirects(t_redir *redir);
void	update_exit_status(t_shell *shell, int status);
void	exit_built_in(t_shell *shell);
void	clean_exit(t_shell *shell);
int		apply_heredoc(t_redir *redir);
int		ft_setup_heredocs(t_cmd *cmds);
int		apply_redirects(t_redir *redir);
void	external_cmd_exit(t_shell *shell, char *path, int status);
void	parse_external_cmd_path(t_shell *shell, char *path);
void	parse_external_cmd_execve(t_shell *shell, char *path, int error);

#endif
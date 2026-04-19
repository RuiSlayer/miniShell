/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/04/19 01:07:24 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

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
# include <sys/stat.h>
# include <linux/limits.h>
# include "expansion.h"
# include "shell.h"
# include <sysexits.h>
# include "../ft_get_next_line/get_next_line.h"

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_fd;
	int		pipe_count;
	t_cmd	*cmd;
	pid_t	last_pid;
	pid_t	*pids;
}	t_pipe;

extern volatile sig_atomic_t	g_signal;

# define GREEN      "\x01\033[32m\x02"
# define BLUE_NEON  "\x01\033[38;5;27m\x02"
# define RED        "\x01\033[1;31m\x02"
# define RST        "\x01\033[0m\x02"

# define CHILD_RUNNING	100
# define HEREDOC_RUNNING	200

int		echo(t_cmd	*cmd);
int		pwd(void);
int		built_export(t_cmd *cmds, t_env **env);
int		unset(t_cmd *cmds, t_env **env);
int		print_env(t_env *env);
int		cd(t_cmd *cmds, t_env **env);
void	setup_signals(void);
char	*ft_find_path(t_shell *shell, char *cmd, t_env *env);
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
int		apply_heredoc(t_redir *redir, t_shell *shell);
int		ft_setup_heredocs(t_cmd *cmds, t_shell *shell);
void	external_cmd_exit(t_shell *shell, char *path, int status);
void	parse_external_cmd_path(t_shell *shell, char *path);
void	parse_external_cmd_execve(t_shell *shell, char *path, int error);
void	print_banner(void);
char	*get_prompt(void);
void	pipe_setup(t_pipe **pipe_s, t_shell *shell);
void	set_status(t_shell *shell, int status);
void	redirect_no_coms(t_shell *shell, t_pipe *pipe_s);
void	child_signals(void);
void	heredoc_signals(void);
int		heredoc_event_hook(void);
void	close_fd_heredocs(t_cmd *cmd);
void	close_fd_all_heredocs(t_cmd *cmds);
void	free_pipe(t_pipe *pipe_s);
void	close_fd(int *fd);
int		print_export(t_env **env);
int		parse_var_name(char *arg);
void	ft_strip_quoted(char *str, int *i, char **result);
char	*ft_strip_delimiter(char *str);
char	*expand_heredoc(char *line, t_shell *shell);
int		open_fd(t_redir	*redir);
int		clear_after(char *line, int pipefd[], char *delimiter, t_redir *redir);
#endif
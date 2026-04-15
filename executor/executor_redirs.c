/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:14:58 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/15 03:24:12 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

/* static char	*ft_strip_delimiter(char *str)
{
	char	*result;
	int		i;
	char	quote;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				ft_append_char(&result, str[i]);
				i++;
			}
			if (str[i])
				i++;
		}
		else
		{
			ft_append_char(&result, str[i]);
			i++;
		}
	}
	return (result);
} */

static void	ft_strip_quoted(char *str, int *i, char **result)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		ft_append_char(result, str[*i]);
		(*i)++;
	}
	if (str[*i])
		(*i)++;
}

static char	*ft_strip_delimiter(char *str)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_strip_quoted(str, &i, &result);
		else
		{
			ft_append_char(&result, str[i]);
			i++;
		}
	}
	return (result);
}

int	clear_after_heredoc(char *line, int pipefd[], char *delimiter, t_redir *redir)
{
	free(line);
	free(delimiter);
	setup_signals();
	close(pipefd[1]);
	rl_event_hook = NULL;
	redir->heredoc_fd = pipefd[0];
	return (0);
}

int	heredoc_loop_breaks(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		return (1);
	}
	if (g_signal == SIGINT)
		return (1);
	if (!line || ft_strcmp(line, delimiter) == 0)
		return (1);
	return (0);
}

int	apply_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;
	char	*delimiter;

	g_signal = HEREDOC_RUNNING;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	delimiter = ft_strip_delimiter(redir->file);
	if (!delimiter)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	g_signal = HEREDOC_RUNNING;
	heredoc_signals();
	rl_event_hook = heredoc_event_hook;
	while (1)
	{
		line = readline("> ");
		if (heredoc_loop_breaks(line, delimiter))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	return (clear_after_heredoc(line, pipefd, delimiter, redir));
}

/* int	apply_heredoc(t_redir *redir)
{
    int		pipefd[2];
    char	*line;
    char	*delimiter;

    if (pipe(pipefd) == -1)
        return (perror("pipe"), -1);
    delimiter = ft_strip_delimiter(redir->file);
    if (!delimiter)
        return (close(pipefd[0]), close(pipefd[1]), -1);
    g_signal = HEREDOC_RUNNING;
    heredoc_signals();              // <-- replaces your bare g_signal = HEREDOC_RUNNING
	rl_event_hook = heredoc_event_hook;
    while (1)
    {
        line = readline("> ");
        if (g_signal == SIGINT)     // <-- Ctrl+C: readline returned via rl_done
        {
            free(line);
            line = NULL;
            break ;
        }
        if (!line || ft_strcmp(line, delimiter) == 0)
            break ;
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    free(line);
    free(delimiter);
    close(pipefd[1]);
    setup_signals();                // <-- restore normal interactive handlers
    rl_event_hook = NULL;
    if (g_signal == SIGINT)
    {
        close(pipefd[0]);
        rl_cleanup_after_signal();  // restores terminal settings
        rl_reset_after_signal();    // reinitializes readline internals
        return (-1);
    }
    redir->heredoc_fd = pipefd[0];
    return (0);
} */


int	ft_setup_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (apply_heredoc(redir) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	open_fd(t_redir	*redir)
{
	if (redir->type == R_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == R_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == R_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

int	apply_redirects(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		else
		{
			fd = open_fd(redir);
			if (fd == -1)
				return (perror(redir->file), -1);
			if (redir->type == R_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:14:58 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/11 19:36:55 by slayer           ###   ########.fr       */
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

int	apply_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;
	char	*delimiter;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	delimiter = ft_strip_delimiter(redir->file);
	if (!delimiter)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	free(delimiter);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

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

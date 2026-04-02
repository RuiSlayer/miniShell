/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:36:17 by slayer            #+#    #+#             */
/*   Updated: 2026/04/02 21:17:40 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

/* static char	*left_trim(char *line)
{
	char	*ptr_line;

	ptr_line = ft_strdup(line);
	if ((ptr_line[4] == ' ' || ptr_line[4] == '\t' || ptr_line[4] == '\0'))
		ptr_line += 4;
	while (*ptr_line == ' ' || *ptr_line == '\t')
		ptr_line++;
	return (ptr_line);
}

char	*right_trim(char *s)
{
	char	*end;

	if (s == NULL || *s == '\0')
		return (s);
	end = s + ft_strlen(s) - 1;
	while (end >= s && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (s);
}

static char	*get_content(char *line)
{
	char	*content;
	char	*p;

	content = left_trim(line);
	p = content;
	while (*p != '\0' && *p != '>')
		p++;
	*p = '\0';
	content = right_trim(content);
	return (content);
}

static char	*get_file(char *line)
{
	char	*file;
	int		i;

	file = ft_strdup(line);
	if (!file || !*file)
		return (NULL);
	i = ft_strlen(file) - 1;
	if (i == 0)
		return (NULL);
	while (i >= 0 && file[i] != '>')
		i--;
	if (i < 0)
	{
		free(file);
		return (NULL);
	}
	file = file + i + 1;
	while (*file == ' ')
		file++;
	return (file);
}

int	echo_cmd_std(char *line)
{
	int		i;
	char	*ptr_line;

	ptr_line = left_trim(line);
	i = 0;
	while (ptr_line[i])
	{
		if (ptr_line[i] == '\"')
		{
			i++;
			continue ;
		}
		write (1, &ptr_line[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	echo_cmd_redir(char *line)
{
	char	*content;
	char	*file;
	int		i;
	int		fd;

	content = get_content(line);
	file = get_file(line);
	fd = open (file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open failed");
		return (1);
	}
	i = 0;
	while (content[i])
	{
		write(fd, &content[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
	return (0);
} */
static int		echo_n(char **args, int *newline)
{
	int	i;
	int	j;

	*newline = 1;
	i = 1;
	while (args[i])
	{
		if (strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*newline = 0;
				i++;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}
int		echo(t_cmd	*cmd)
{
	int		i;
	int		newline;

	i = echo_n(cmd->args, &newline);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

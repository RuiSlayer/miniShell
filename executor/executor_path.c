/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:14:59 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/31 20:00:13 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"

static char	*ft_try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*ft_find_path(char *cmd, t_env *env)
{
	char	**dirs;
	int		i;
	char	*path_env;
	char	*full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		return cmd;
	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (printf("minishell: PATH not set\n"), NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (*dirs[i])
	{
		full_path = ft_try_path(&dirs[i], cmd);
		if (full_path)
			return (ft_free_split(dirs), full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

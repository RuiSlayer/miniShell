/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:14:59 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/07 04:37:13 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

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

void	ft_free_double_pointer(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	*ft_find_path(char *cmd, t_env *env)
{
	char	**dirs;
	int		i;
	char	*path_env;
	char	*full_path;

	if (ft_strchr(cmd, '/') || ft_strncmp(cmd, "./", 3) == 0)
		return ft_strdup(cmd);
	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (printf("minishell: PATH not set\n"), NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = ft_try_path(dirs[i], cmd);
		if (full_path)
			return (ft_free_double_pointer(dirs), full_path);
		i++;
	}
	return (ft_free_double_pointer(dirs), NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/02/25 02:06:09 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

void	update_pwd(char *old_pwd, t_env *env)
{
	char *new_pwd;
	char *tmp;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (tmp)
	{
		add_var(tmp, env);
		free(tmp);
	}

	tmp = ft_strjoin("PWD=", new_pwd);
	if (tmp)
	{
		add_var(tmp, env);
		free(tmp);
	}

	free(new_pwd);
}

int	cd(char *line, t_env *env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (printf("pwd: error retrieving current directory: %s\n", strerror(errno)), 1);
	if (line == NULL || line[0] == '\0')
	{
		home = getenv("HOME");
		if (!home)
			return (fprintf(stderr, "cd: HOME not set\n"), -1);
		if (chdir(home) != 0)
			return (perror("cd"),free(old_pwd), 1);
		return (update_pwd(old_pwd, env), free(old_pwd), 0);
	}
	if (line[0] == '.' && line[1] == '.' && line[2] == '\0')
	{
		if (chdir("..") != 0)
			return (perror("cd"),free(old_pwd), 1);
		return (update_pwd(old_pwd, env), free(old_pwd), 0);
	}
	if (chdir(line) != 0)
		return (perror("cd"), free(old_pwd), 1);
	return (update_pwd(old_pwd, env), free(old_pwd), 0);
}

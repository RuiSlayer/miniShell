/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/03/11 14:38:03 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	update_pwd(char *old_pwd, t_env **env)
{
	char	*new_pwd;
	char	*tmp;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_pwd), 1);
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
	free(old_pwd);
	return (0);
}

int	cd(char *line, t_env **env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd: error retrieving current directory\n"), 1);
	if (line == NULL || line[0] == '\0')
	{
		home = getenv("HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), free(old_pwd), 1);
		if (chdir(home) != 0)
			return (perror("cd\n"), free(old_pwd), 1);
		return (update_pwd(old_pwd, env));
	}
	if (chdir(line) != 0)
		return (perror("cd\n"), free(old_pwd), 1);
	return (update_pwd(old_pwd, env));
}

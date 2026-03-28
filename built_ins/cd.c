/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/03/28 21:19:06 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

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

int	cd(t_cmd *cmds, t_env **env)
{
	char	*old_pwd;
	char	*home;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("minishell: cd: OLDPWD not set\n"), 1);
	if(!cmds->args[1])
	{
		home = ft_getenv(*env, "HOME");
		if(!home || home[0])
			return(printf("minishell: cd: HOME not set\n"), free(old_pwd), 1);
		if (chdir(home) != 0)
			return (perror("cd"), free(old_pwd), 1);
		return (update_pwd(old_pwd, env), 0);
	}
	if (chdir(cmds->args[1]) != 0)
		return (perror("cd"), free(old_pwd), 1);
	return (update_pwd(old_pwd, env), 0);
}

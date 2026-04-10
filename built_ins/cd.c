/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/04/11 00:35:45 by slayer           ###   ########.fr       */
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

int	change_dir(char *dir, char	*old_pwd, t_env **env)
{
	if (chdir(dir) != 0)
		return (perror("cd"), free(old_pwd), 1);
	return (update_pwd(old_pwd, env), 0);
}

int	chage_by_var(char *old_pwd, t_env **env, char *name)
{
	char	*val;

	val = ft_getenv(*env, name);
	if (!val || ft_strcmp(val, "") == 0)
		return (printf("minishell: cd: %s not set\n", name), free(old_pwd), 1);
	return (change_dir(val, old_pwd, env), 0);
}

int	cd(t_cmd *cmds, t_env **env)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!cmds->args[1])
		return (chage_by_var(old_pwd, env, "HOME"));
	if (ft_strcmp(cmds->args[1], "--") == 0 && cmds->args[2])
		return (change_dir(cmds->args[2], old_pwd, env));
	if (cmds->args[2])
		return (printf("minishell: cd: too many arguments\n"),
			free(old_pwd), 1);
	if (ft_strcmp(cmds->args[1], "-") == 0)
	{
		if (chage_by_var(old_pwd, env, "OLDPWD"))
			return (1);
		return (printf("%s\n", ft_getenv(*env, "OLDPWD")));
	}
	return (change_dir(cmds->args[1], old_pwd, env));
}

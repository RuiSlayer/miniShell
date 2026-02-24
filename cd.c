/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/02/24 23:02:48 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	cd(char *line, t_env *env)
{
	char	*home;

	if (line == NULL || line[0] == '\0')
	{
		home = getenv("HOME");
		if (!home)
			return (fprintf(stderr, "cd: HOME not set\n"), -1);
		if (chdir(home) != 0)
			return (perror("cd"), -1);
		return (0);
	}
	if (line[0] == '.' && line[1] == '.' && line[2] == '\0')
	{
		if (chdir("..") != 0)
			return (perror("cd"), -1);
		return (0);
	}
	if (chdir(line) != 0)
		return (perror("cd"), -1);
	return (0);
	/* need updating PWD and OLDPWD in your t_env after successful chdir calls */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:55:19 by slayer            #+#    #+#             */
/*   Updated: 2026/01/29 18:31:57 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42libft/libft.h"
#include "miniShell.h"

static int	go_back_one_dir(char *line)
{
	char	*value;
	int		i;

	value = getenv("PWD");
	i = ft_strlen(value);
	while(i > 0 && value[i] != '/')
		i--;
	value[i] = '\0';
	chdir(value);
	return (0);
}

int	cd(char *line)
{
	if (line == NULL || ft_strncmp(line, "", ft_strlen(line)) == 0)
	{
		const char *home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return -1;
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			return (-1);
		}
		return (0);
	}
	if(ft_strncmp(line, "..", ft_strlen(line)) == 0)
		return (go_back_one_dir(line));
	if (chdir(line) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

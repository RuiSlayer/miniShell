/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 06:08:49 by slayer            #+#    #+#             */
/*   Updated: 2026/04/14 22:01:11 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	print_banner(void)
{
	char	*line;
	int		fd;

	fd = open("banner.txt", O_RDONLY);
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf(GREEN"%s"RST, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
}

char	*get_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*prompt;

	getcwd(cwd, PATH_MAX);
	tmp = ft_strjoin(BLUE_NEON, cwd);
	prompt = ft_strjoin(tmp, GREEN"$> "RST);
	free(tmp);
	return (prompt);
}

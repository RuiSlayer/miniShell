/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 06:08:49 by slayer            #+#    #+#             */
/*   Updated: 2026/04/11 16:20:11 by slayer           ###   ########.fr       */
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

char	*get_prompt()
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*prompt;

	getcwd(cwd, PATH_MAX);
	tmp = ft_strjoin(BBLUE, cwd);
	prompt = ft_strjoin(tmp, BLUE_NEON"$> "RST);
	free(tmp);

	return (prompt);
}

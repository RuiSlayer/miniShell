/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 06:08:49 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 19:58:19 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void clear_terminal(void)
{
	write(1, "\033[H\033[2J", 7);
}

void	print_banner(void)
{
	char	*line;
	int		fd;
	clear_terminal();
	fd = open("banner.txt", O_RDONLY);
	if (fd < 0)
		return ;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf(GREEN"%s"RST, line);
		free(line);
		line = get_next_line(fd);
	}
	close_fd(&fd);
	get_next_line(-1);
}

char	*get_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*prompt;

	if (!getcwd(cwd, PATH_MAX))
		return (strdup("prompt$> "));
	tmp1 = ft_strjoin(BLUE_NEON, cwd);
	tmp2 = ft_strjoin(tmp1, RST);
	tmp3 = ft_strjoin(tmp2, GREEN);
	prompt = ft_strjoin(tmp3, "$> " RST);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	return (prompt);
}

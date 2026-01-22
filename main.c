/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/01/21 23:21:59 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

int	echo_cmd(char *line)
{
	printf("%s\n", line);
	return (0);
}

int	cmd_eval(char *line)
{
	char *p = line;

	while (*p == ' ' || *p == '\t')
		p++;
	if (strcmp(line, "exit") == 0)
		return (1);
	if (strcmp(line, "echo") == 0)
		echo_cmd(p);
	return (0);
}

int	main(void)
{
	char *line;

	while (1) {
		line = readline("prompt> ");
		if (line == NULL)
			return (0);
		if (cmd_eval(line))
			return (free(line), 0);
		if (*line)                   // non-empty line
			add_history(line);
		/* printf("You typed: %s\n", line); */
		free(line);                  // important: readline() uses malloc()
	}
	return (0);
}

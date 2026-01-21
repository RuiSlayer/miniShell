/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/01/21 22:27:01 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

int	exit_cmd(char *line)
{
	char *p = line;

	while (*p == ' ' || *p == '\t')
		p++;
	if (strcmp(p, "exit") == 0) {   // "exit" -> quit
		return (1);
	}
	return (0);
}

int	main(void)
{
	char *line;


	while (1) {
		line = readline("prompt> ");
		if (line == NULL)
			return (0);
		if (exit_cmd(line))
			return (free(line), 0);
		if (*line)                   // non-empty line
			add_history(line);
		printf("You typed: %s\n", line);
		free(line);                  // important: readline() uses malloc()
	}


	return (0);
}

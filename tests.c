/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:32:25 by slayer            #+#    #+#             */
/*   Updated: 2026/01/29 18:36:32 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

static int	go_back_one_dir(void)
{
	char	*value;
	int		i;

	value = getenv("PWD");
	i = strlen(value);
	while(i > 0 && value[i] != '/')
		i--;
	value[i] = '\0';
	printf("%s\n", value);
	/* chdir(value); */
	return (0);
}

int main(void)
{
	go_back_one_dir();
}
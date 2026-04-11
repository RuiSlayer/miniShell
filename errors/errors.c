/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:00 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/11 20:15:28 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/errors.h"
#include "../ft_dprintf/ft_printf.h"

void	ft_syntax_error(char *token)
{
	if (token)
	{
		// update_exit_status(shell, 2);
		ft_dprintf(2,
			"minishell: syntax error near unexpected token `%s'\n", token);
	}
	else
	{
		// update_exit_status(shell, 2);
		ft_dprintf(2, "minishell: syntax error near unexpected token");
	}
}

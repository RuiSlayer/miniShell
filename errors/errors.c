/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:00 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/06 20:07:51 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/errors.h"
#include "../42libft/libft.h"
#include "../ft_dprintf/ft_printf.h"

void	ft_syntax_error(char *token)
{
	if (token)
		ft_dprintf(2, "minishell: syntax error near unexpected token  `%s'\n", token);
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token");
}

void	ft_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

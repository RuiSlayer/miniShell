/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:00 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/02 21:17:11 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/errors.h"
#include "../42libft/libft.h"

void	ft_syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", 2);
	if (token)
	{
		ft_putstr_fd("syntax error near unexpected token  `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("syntax error near unexpected token", 2);
}

void	ft_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

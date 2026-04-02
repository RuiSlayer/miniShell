/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:20:06 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/02 19:43:02 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "tokens.h"

void	ft_syntax_error(char *token);

# define ERR_SYNTAX_PIPE "syntax error near unexpected token '|'"
# define ERR_SYNTAX_REDIR "syntax error near unexpected token"
# define ERR_SYNTAX_TOKEN "syntax error near unexpected token"
# define ERR_MALLOC "memory allocation failed"

#endif
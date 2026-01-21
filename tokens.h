/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:10:22 by fgameiro          #+#    #+#             */
/*   Updated: 2026/01/21 23:23:00 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_token_type
{
    T_AND,
    T_OR,
    T_PIPES,
    T_LESS,
    T_MORE,
    T_DLESS,
    T_DMORE,
    T_OPERATORS,
    T_DATATYPE,
}   t_toke_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

#endif TOKENS_H
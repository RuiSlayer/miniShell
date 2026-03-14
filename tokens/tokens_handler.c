/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:29:21 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/14 17:26:24 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

int ft_handle_separator(char **line_ptr, t_token **token_list)
{
    if (!ft_strncmp(*line_ptr, "<<", 2))
        return (ft_append_separator(T_DLESS, line_ptr, token_list));
    else if (!ft_strncmp(*line_ptr, ">>", 2))
        return (ft_append_separator(T_DGREAT, line_ptr, token_list));
    else if (**line_ptr == '<')
        return (ft_append_separator(T_LESS, line_ptr, token_list));
    else if (**line_ptr == '>')
        return (ft_append_separator(T_GREAT, line_ptr, token_list));
    else if (**line_ptr == '|')
        return (ft_append_separator(T_PIPE, line_ptr, token_list));
    return (0);
}

t_token	*ft_tokenization_handler(char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (ft_clear_token_list(&token_list), NULL);
		if (ft_isspace(*line))
			ft_skip_spaces(&line);
		else if (*line == '<' || *line == '>' || *line == '|')
            error = (!ft_handle_separator(&line, &token_list));
		else
			error = (!ft_append_identifier(&line, &token_list));
	}
    ft_token_list_add_back(&token_list, ft_new_token(NULL, T_EOF));
	return (token_list);
}
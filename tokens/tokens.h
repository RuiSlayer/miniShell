/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:10:22 by fgameiro          #+#    #+#             */
/*   Updated: 2026/02/24 22:18:46 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include <stdbool.h>//booleans
# include <stdio.h>//printf
# include <stdlib.h>
# include <stddef.h>
# include "42libft/libft.h"
typedef enum e_token_type
{
    T_IDENTIFIER,
    T_PIPE,
    T_LESS,
    T_GREAT,
    T_DLESS,
    T_DGREAT,
    T_EOF
} t_token_type;


typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

int     ft_append_separator(t_token_type type, char **line_ptr,
t_token **token_list);
int     ft_append_identifier(char **line_ptr, t_token **token_list);
int     ft_handle_separator(char **line_ptr, t_token **token_list);
t_token	*ft_tokenization_handler(char *line);
t_token *ft_new_token(char *value, t_token_type type);
void    ft_token_list_add_back(t_token **lst, t_token *new_token);
void    ft_clear_token_list(t_token **lst);
const char *token_type_to_str(t_token_type type);
void    print_tokens(t_token *tokens);
int	    ft_is_quote(char c);
int	    ft_is_separator(char *s);
void	ft_skip_spaces(char **line);
bool	ft_skip_quotes(char *line, size_t *i);
int     ft_isspace(int c);

#endif
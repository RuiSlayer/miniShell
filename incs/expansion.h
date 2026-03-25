/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:50 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/25 00:30:36 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "shell.h"
# include "../42libft/libft.h"

// entry point
void    ft_expand(t_shell *shell);

// main string transformer
char    *ft_expand_string(char *str, t_shell *shell);

// handlers
void    ft_handle_single_quote(char *str, size_t *i, char **result);
void    ft_handle_double_quote(char *str, size_t *i, char **result, t_shell *shell);
void    ft_handle_expansion(char *str, size_t *i, char **result, t_shell *shell);

// helpers
char    *ft_get_var_name(char *str, size_t *i);
void    ft_append_str(char **result, char *str);
void    ft_append_char(char **result, char c);



#endif
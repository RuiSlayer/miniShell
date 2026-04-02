/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:50 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/02 19:18:16 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "parser.h"
# include "shell.h"

// entry point
void	ft_expand(t_shell *shell);

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
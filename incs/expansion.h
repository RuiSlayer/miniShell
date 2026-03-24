/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:50 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/24 16:36:53 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "miniShell_exec.h"

// entry point
void    ft_expand(t_cmd *cmds, char **envp, int exit_status);

// main string transformer
char    *ft_expand_string(char *str, char **envp, int exit_status);

// handlers
void    ft_handle_single_quote(char *str, size_t *i, char **result);
void    ft_handle_double_quote(char *str, size_t *i, char **result, char **envp, int exit_status);
void    ft_handle_expansion(char *str, size_t *i, char **result, char **envp, int exit_status);

// helpers
char    *ft_get_var_name(char *str, size_t *i);
char    *ft_get_env_value(char **envp, char *var_name);
void    ft_append_str(char **result, char *str);
void    ft_append_char(char **result, char c);
char	ft_getenv(char **env, char *name);



#endif
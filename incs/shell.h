/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:29:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/07 18:25:05 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "env.h"
# include "parser.h"

typedef struct s_shell
{
    t_env   *env;
    t_cmd   *cmds;
    short     exit_status;
    int     cmd_count;
    int is_subshell;
}   t_shell;

#endif
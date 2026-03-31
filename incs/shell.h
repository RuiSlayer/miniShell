/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:29:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/31 19:52:20 by rucosta          ###   ########.fr       */
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
    int     exit_status;
    int     cmd_count;
}   t_shell;

#endif
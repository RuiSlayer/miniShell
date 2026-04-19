/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:29:36 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/18 22:53:43 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "env.h"
# include "parser.h"

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	t_cmd	*cmds_head;
	short	exit_status;
	int		cmd_count;
	int		saved_in;
	int		saved_out;
	int		is_inchild;
}	t_shell;

#endif
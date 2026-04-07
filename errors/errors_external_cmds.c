/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_external_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 03:26:41 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/07 03:53:19 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	external_cmd_exit(t_shell *shell, char *path, int status)
{
	update_exit_status(shell, status);
	free(path);
	clean_exit(shell);
}

void	parse_external_cmd_path(t_shell *shell, char *path)
{
	if (!path || access(path, F_OK) != 0)
	{
		if (errno == ENOTDIR)
		{
			ft_dprintf(2, "%s : Not a directory\n", shell->cmds->args[0]);
			return (external_cmd_exit(shell, path, 126));
		}
		if (ft_strchr(shell->cmds->args[0], '/') || ft_strncmp(shell->cmds->args[0], "./", 2) == 0)
			ft_dprintf(2, "%s : No such file or directory\n", shell->cmds->args[0]);
		return (external_cmd_exit(shell, path, 127));
	}
}

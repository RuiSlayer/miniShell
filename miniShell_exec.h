/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniShell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:38 by slayer            #+#    #+#             */
/*   Updated: 2026/02/26 17:59:05 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISELL_EXEC
# define MINISELL_EXEC
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/chardefs.h>
# include "42libft/libft.h"


typedef struct s_env
{
	char	*var;
	char	*val;
	int		idx;
	struct s_env *next;
}	t_env;

int		echo_cmd_std(char *line);
int		echo_cmd_redir(char *line);
int		pwd(void);
int		export(char **args, t_env *env);
int		unset(char **args, t_env *env);
int		print_env(t_env *env);
void	save_env(t_env **env, char **envp);
void	add_var(char *line, t_env *env);
int		cd(char *line, t_env *env);
void	add_var(char *line, t_env *env);
void	remove_var(char *arg, t_env *env);



#endif
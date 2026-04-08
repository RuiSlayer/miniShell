/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 21:56:02 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/08 02:29:59 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "errors.h"

typedef struct s_env
{
	char			*var;
	char			*val;
	int				idx;
	struct s_env	*next;
}	t_env;

void	free_env(t_env *env);
void	save_node(t_env **env, char *envp, int i);
void	save_env(t_env **env, char **envp);
void	add_var(char *arg, t_env **env);
void	remove_var(char *arg, t_env **env);
char	**env_to_array(t_env *env);
char	*ft_getenv(t_env *env, char *name);
#endif
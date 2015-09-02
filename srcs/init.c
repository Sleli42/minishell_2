/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:07:46 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/01 07:54:34 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	**ft_dupenv(char **env)
{
	char	**dup;
	int		i;

	i = -1;
	if (!(dup = (char **)malloc(sizeof(char *) * ft_tablen(env) + 1)))
		return (NULL);
	while (++i < (int)ft_tablen(env))
		dup[i] = ft_strdup(env[i]);
	dup[++i] = NULL;
	return (dup);
}

t_all	*init_all(char **env)
{
	t_all	*all;
	int		i;

	i = 0;
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	all->dupenv = ft_dupenv(env);
	all->env = create_dlst();
	all->cmd2exec = NULL;
	all->redirection = NULL;
	all->cmd = NULL;
	all->redirect_cmd = (char *)malloc(sizeof(char));
	while (env[i])
		dlst_add_back(all->env, dlst_new(env[i++]));
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	exit(1);
	all->redir_name = R_NULL;
	return (all);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:07:46 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/26 02:42:26 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

t_all	*init_all(char **env)
{
	t_all	*all;
	int		i;

	i = 0;
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	all->env = create_dlst();
	all->cmd = NULL;
	while (env[i])
		dlst_add_back(all->env, dlst_new(env[i++]));
	all->path2exec = ft_strsplit(all->env->head->s + 6, ':');
	return (all);
}

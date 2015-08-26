/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 04:12:12 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/26 04:09:36 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	try_builtins_cmd(t_all *all)
{
	int				i;
	t_builtins		built[] =

	{
		{"env", env_display},
		{"set env", env_set},
		{"unset env", env_unset},
		{"pwd", pwd_display},
		{"cd", goto_dir},
		{"exit", free_all}
	};
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(all->cmd, built[i].builtin_name,
			ft_strlen(built[i].builtin_name)) == 0)
			built[i].f(all);
		i++;
	}
}

void	try_exec_cmd(t_all *all)
{

}

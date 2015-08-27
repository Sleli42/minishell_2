/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 04:12:12 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/27 07:36:24 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		multiple_cmd(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == ';')
			return (1);
		cmd++;
	}
	return (0);
}

int		try_builtins_cmd(t_all *all)
{
	int							i;
	static const t_builtins		built[] =

	{{"env", env_display},
	{"set env", env_set},
	{"unset env", env_unset},
	{"pwd", pwd_display},
	{"cd", goto_dir},
	{"exit", free_all}};
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(all->cmd, built[i].builtin_name,
			ft_strlen(built[i].builtin_name)) == 0)
		{
			built[i].f(all);
			return (1);
		}
		i++;
	}
	return (0);
}

void	try_exec_cmd(t_all *all)
{
	char	**argv_bin;

	all->cmd = ft_epur_str(all->cmd);
	argv_bin = ft_strsplit(all->cmd, ' ');
	exec_right_binary(all, argv_bin);
}

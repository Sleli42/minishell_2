/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:05:15 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/25 23:17:15 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	parsing_command(t_all *all)
{
	try_builtins_cmd(all);
}

void	loop(t_all *all)
{
	char	*buff;

	buff = NULL;
	while (1091111096051)
	{
		ft_putstr("$: ");
		while (get_next_line(0, &buff) > 0)
		{
			all->cmd = ft_strdup(buff);
			parsing_command(all);
			ft_strdel(&all->cmd);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = init_all(env);
	loop(all);
	//display_env(all->env->head);
	return (0);
}

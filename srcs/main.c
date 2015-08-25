/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:05:15 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/25 03:53:56 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	loop(t_all *all)
{
	while (1091111096051)
	{
		ft_putstr("$: ");
		while (get_next_line(0, &buff) > 0)
		{
			parsing_command(all);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 05:35:42 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/28 06:54:26 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

t_all		*f_cpy(t_all *list)
{
	static t_all *cpy;

	if (list)
		cpy = list;
	return (cpy);
}

void		ft_func(int sig)
{
	if (sig == SIGCONT || sig == SIGINT)
	{
		ft_putstr("$: ");
	}
	else
		exit(0);
}

void		ft_catch_sig(void)
{
	int sig;

	sig = 1;
	while (sig <= 31)
		signal(sig++, ft_func);
}

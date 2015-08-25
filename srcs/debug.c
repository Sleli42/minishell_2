/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:29:45 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/25 22:42:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	display_env(t_node *env)
{
	t_node	*tmp;

	tmp = env;
	if (tmp)
	{
		while (tmp)
		{
			printf("%s\n", tmp->s);
			tmp = tmp->next;
		}
	}
}

void	display_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

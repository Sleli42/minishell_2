/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 04:12:12 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/25 23:18:17 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

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
		{"exit", free_all},
	}
}

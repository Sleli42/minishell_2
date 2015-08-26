/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:23:36 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/26 02:42:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	error(char *err)
{
	if (ft_strcmp(err, "MALLOC") == 0)
		ft_putendl("Malloc error.");
	if (ft_strcmp(err, "DIR") == 0)
		ft_putendl("cd '/dir/' error.");
}

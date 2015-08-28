/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 23:30:44 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/28 23:36:26 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strstr(char *s, char *tofind)
{
	char	*ret;
	int		i;
	int		j;

	ret = NULL;
	i = 0;
	j = ft_strlen(tofind);
	while (s[i])
	{
		if (s[i] == tofind[j])
			j--;
		if (j == 0)
		{
			ret = ft_strdup(tofind);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 22:05:55 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/28 07:30:14 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_epur_str(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(ret = (char *)malloc(sizeof(char *))))
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
	    	ret[j++] = ' ';
			while (s[i] == ' ' || s[i] == '\t')
                i++;
		}
		ret[j++] = s[i++];
	}
	ret[j] = '\0';
	return (ret);
}

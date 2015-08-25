/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:42:32 by lubaujar          #+#    #+#             */
/*   Updated: 2015/06/05 16:39:39 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				count_words(char *s, char c)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
				ret++;
			i++;
		}
		ret = ret + 1;
	}
	return (ret);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		ct;
	int		i;
	int		j;

	ct = 0;
	i = 0;
	if (!(array = (char **)malloc(sizeof(char *)
		* count_words((char*)s, c) + 1)))
		return (NULL);
	while (ct < count_words((char*)s, c))
	{
		j = 0;
		array[ct] = (char *)malloc(sizeof(char) * 42);
		while (s[i] && s[i] != c)
			array[ct][j++] = s[i++];
		array[ct][j] = '\0';
		i++;
		ct++;
	}
	array[ct] = NULL;
	return (array);
}

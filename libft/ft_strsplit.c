/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:42:32 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/29 05:15:12 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	ct;

	ct = 0;
	if (!(ret = (char *)malloc(sizeof(char) * n)))
		return (NULL);
	while (ct < n)
	{
		ret[ct] = s[ct];
		ct++;
	}
	ret[ct] = '\0';
	return (ret);
}

int				count_words(char *s, char c)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (s && s[i])
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
	int		stop;
	int		i;

	ct = 0;
	i = 0;
	stop = count_words((char *)s, c);
	write(1, "hello\n", 6);
	if (!(array = (char **)malloc(sizeof(char *) * stop + 1)))
		return (NULL);
	while (ct < stop)
	{
		while (s[i] && s[i] != c)
			i++;
		array[ct] = ft_strndup((char *)s, (size_t)i);
		//ft_strdup(ft_strncpy(array[ct], (char *)s, (size_t)i));
		printf("%s\n", array[ct]);
		i++;
		ct++;
		// if (array[ct][j - 1] == ' ')
		// 	array[ct][j - 1] = '\0';
		// else
	}
	array[ct] = NULL;
	return (array);
}

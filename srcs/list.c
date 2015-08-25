/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:12:26 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/25 03:41:32 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

t_dlist		*create_dlst(void)
{
	t_dlist	*new;

	new = (t_dlist*)malloc(sizeof(t_dlist));
	if (new != NULL)
	{
		new->lenght = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}

t_node		*dlst_new(char *data)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new)
	{
		new->s = ft_strdup(data);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_dlist		*dlst_add_back(t_dlist *lst, t_node *node)
{
	if (lst && node)
	{
		if (lst->tail == NULL)
		{
			lst->head = node;
			lst->tail = node;
		}
		else
		{
			lst->tail->next = node;
			node->prev = lst->tail;
			lst->tail = node;
		}
		lst->lenght++;
	}
	return (lst);
}

// t_dlist		*dlst_del_one(t_dlist *lst, int data2del)
// {
// 	t_node	*tmp;
// 	int		found;

// 	tmp = lst->head;
// 	found = 0;
// 	if (lst)
// 	{
// 		while (tmp && !found)
// 		{
// 			if (tmp->data == data2del)
// 			{
// 				if (!tmp->next && !tmp->prev)
// 				{
// 					free(lst);
// 					lst = create_dlst();
// 					return (lst);
// 				}
// 				else
// 					found = update_list(lst, tmp);
// 				free(tmp);
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (lst);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:05:42 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/26 04:12:12 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct			s_node
{
	char				*s;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_dlist
{
	struct s_node		*head;
	struct s_node		*tail;
	size_t				lenght;
}						t_dlist;

typedef struct			s_all
{
	t_dlist				*env;
	char				*cmd;
	char				*oldpwd;
	char				**path2exec;
}						t_all;

typedef	struct			s_builtins
{
	char				*builtin_name;
	void				(*f)(t_all *);

}						t_builtins;
/*
***	init.c
*/
t_all			*init_all(char **env);
/*
***	list.c
*/
t_dlist			*create_dlst(void);
t_node			*dlst_new(char *data);
t_dlist			*dlst_add_back(t_dlist *lst, t_node *node);
t_dlist			*dlst_del_one(t_dlist *lst, char *arg2del);
int				update_list(t_dlist *lst, t_node *elem);
/*
***	env.c
*/
void			env_display(t_all *all);
void			env_set(t_all *all);
void			env_unset(t_all *all);
/*
***	builtins.c
*/
void			try_builtins_cmd(t_all *all);
/*
***	tools.c
*/
void			update_OLDPWD(t_all *all);
void			pwd_display(t_all *all);
char			*find_oldpwd_arg(t_all *all);
void			goto_dir(t_all *all);
void			free_all(t_all *all);
/*
***	error.c
*/
void			error(char *err);
/*
***	debug.c
*/
void			display_env(t_node *env);
void			display_tab(char **tab);
#endif

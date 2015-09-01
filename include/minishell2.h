/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:05:42 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/01 08:02:08 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include <stdio.h>
# include <sys/types.h>/*			UBUNTU				*/
# include <sys/wait.h>/*			UBUNTU				*/
# include <unistd.h>

# include <stdlib.h>
# include "libft.h"

# define R_NULL	0
# define SRD	1
# define SRG	2
# define DRD	3
# define DRG	4

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
	char				*redirect_cmd;
	char				*oldpwd;
	char				**dupenv;
	char				**cmd2exec;
	char				**path2exec;
	char				**redirection;
	int					redir_name;
	int					fd2open;
	int					fd2read;
}						t_all;

typedef	struct			s_action
{
	char				*action_name;
	void				(*f)(t_all *);

}						t_action;

//void	loop(t_all *all);
/*
***	init.c
*/
t_all			*init_all(char **env);
char			**ft_dupenv(char **env);
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
***	commandes.c
*/
int				multiple_cmd(char *cmd);
int				try_redirection_cmd(t_all *all);
int				try_builtins_cmd(t_all *all);
void			try_exec_cmd(t_all *all);
/*
***	exec_binary.c
*/
int				good_access(char *bin);
char			*create_path(char *path, char *bin);
void			choose_dup(t_all *all);
void			exec_right_binary(t_all *all, char **argv_bin);
void			exec_binary(char *bin, char **argv_bin, char **env);
/*
***	redirection.c
*/
int				check_redirection(char *cmd);
void			erase_and_replace(t_all *all);
void			add_to_end(t_all *all);
void			read_file(t_all *all);
void			read_stdin(t_all *all);
/*
***	tools.c
*/
void			update_oldpwd(t_all *all);
void			pwd_display(t_all *all);
char			*find_env_arg(t_all *all, char *arg2find);
void			goto_dir(t_all *all);
void			free_all(t_all *all);
/*
***	error.c
*/
void			error(char *err);
/*
***	signal.c
*/
t_all			*f_cpy(t_all *list);
void			ft_func(int sig);
void			ft_catch_sig(void);
/*
***	debug.c
*/
void			display_env(t_node *env);
void			display_tab(char **tab);
#endif

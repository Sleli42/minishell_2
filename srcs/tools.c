/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 02:27:17 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/29 10:04:19 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	update_oldpwd(t_all *all)
{
	t_node	*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, "OLDPWD", 6) == 0)
			{
				ft_strdel(&nav->s);
				nav->s = ft_strjoin("OLDPWD=", all->oldpwd);
				return ;
			}
			nav = nav->next;
		}
	}
}

void	pwd_display(t_all *all)
{
	char	*pwd;
	char	*buff;

	(void)all;
	buff = NULL;
	pwd = getcwd(buff, 42);
	ft_putendl(pwd);
}

char	*find_env_arg(t_all *all, char *arg2find)
{
	t_node		*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, arg2find, ft_strlen(arg2find)) == 0)
				return (nav->s);
			nav = nav->next;
		}
	}
	return (NULL);
}

void	goto_dir(t_all *all)
{
	char	*buff;

	buff = NULL;
	all->oldpwd = getcwd(buff, 42);
	all->oldpwd = ft_strjoin(all->oldpwd, "/");
	all->cmd = ft_strdup(all->cmd + 3);
	if (all->cmd[0] == '\0')
		all->cmd = ft_strdup("/nfs/zfs-student-5/users/2014/lubaujar/");
	else if (all->cmd[0] == '-')
		all->cmd = ft_strdup(find_env_arg(all, "OLDPWD") + 7);
	if (access(all->cmd, F_OK) == 0)
	{
		if (chdir(all->cmd) == -1)
			error("DIR");
		update_oldpwd(all);
	}
}

void	free_all(t_all *all)
{
	while (all->env->lenght-- != 0)
		dlst_del_one(all->env, all->env->head->s);
	if (all->path2exec != NULL)
		del_array(&all->path2exec);
	if (all->dupenv != NULL)
		del_array(&all->dupenv);
	if (all->cmd != NULL)
		ft_strdel(&all->cmd);
	free(all);
	all = NULL;
	ft_putendl("exit");
	exit(21);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 04:12:12 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/01 05:10:27 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		multiple_cmd(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == ';')
			return (1);
		cmd++;
	}
	return (0);
}

void		try_redirection_cmd(t_all *all)
{
	int							i;
	static const	t_action	redirection[] =

	{{"|", create_pipe},
	{">", erase_and_replace},
	{">>", add_to_end},
	{"<", read_file},
	{"<<", read_stdin}};
	i = 0;
	all->redirect_cmd = my_strstr(all->cmd);
	if (all->redirect_cmd != NULL)
	{
		while (i < 5)
		{
			if (ft_strcmp(all->redirect_cmd, redirection[i].action_name) == 0)
				redirection[i].f(all);
			i++;
		}
	}
}

int		try_builtins_cmd(t_all *all)
{
	int							i;
	static const t_action		built[] =

	{{"env", env_display},
	{"set env", env_set},
	{"unset env", env_unset},
	{"pwd", pwd_display},
	{"cd", goto_dir},
	{"exit", free_all}};
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(all->cmd, built[i].action_name,
			ft_strlen(built[i].action_name)) == 0)
		{
			built[i].f(all);
			return (1);
		}
		i++;
	}
	return (0);
}

void	try_exec_cmd(t_all *all)
{
	char	**argv_bin;

	all->cmd = ft_epur_str(all->cmd);
	argv_bin = ft_strsplit(all->cmd, ' ');
	exec_right_binary(all, argv_bin);
	del_array(&argv_bin);
}














/* ======================================

char *[0] = c
[1] = a


char : 'c';
char * : "acbde"
char ** 


================================= */















































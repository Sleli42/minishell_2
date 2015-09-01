/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 03:05:15 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/29 10:02:51 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	exec_command(t_all *all)
{
	int		ct;

	ct = 0;
	while (all->cmd2exec[ct])
	{
		ft_strdel(&all->cmd);
		all->cmd = ft_epur_str(all->cmd2exec[ct]);
		//if (all->cmd[ft_strlen(all->cmd) - 1] == ' ')
		//	all->cmd[ft_strlen(all->cmd) - 1] = '\0';
		if (!try_redirection_cmd(all))
			if (!try_builtins_cmd(all))
				try_exec_cmd(all);
		ct++;
	}
	del_array(&all->cmd2exec);
}

char	**parse_command(char *cmd)
{
	char	**cmd2exec;

	cmd2exec = ft_strsplit(cmd, ';');
	return (cmd2exec);
}

void	loop(t_all *all)
{
	char	*buff;

	buff = NULL;
	//f_cpy(all);
	while (1)
	{
		ft_putstr("$: ");
		get_next_line(0, &buff);
		if (*buff == 4)
			free_all(all);
		all->cmd2exec = parse_command(ft_strdup(buff));
		exec_command(all);
	}
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = init_all(env);
	//ft_catch_sig();
	loop(all);
	return (0);
}

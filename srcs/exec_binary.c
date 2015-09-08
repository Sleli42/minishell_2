/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 22:03:11 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/02 08:35:42 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		good_access(char *bin)
{
	if (access(bin, F_OK) == 0)
		if (access(bin, X_OK) == 0)
			return (1);
	return (0);
}

char	*create_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, bin);
	return (tmp);
}

void	exec_right_binary(t_all *all, char **argv_bin)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	while (all->path2exec[ct])
	{
		bin_tmp = create_path(all->path2exec[ct], argv_bin[0]);
		if (good_access(bin_tmp))
			exec_binary(bin_tmp, argv_bin, all->dupenv);
		ft_strdel(&bin_tmp);
		ct++;
	}
}

void	exec_binary(char *bin, char **argv_bin, char **env)
{
	int		buff;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error("FORK");
	if (pid == 0)
		if (execve(bin, argv_bin, env) == -1)
			error("EXECVE");
	if (pid > 0)
		waitpid(pid, &buff, 0);
}

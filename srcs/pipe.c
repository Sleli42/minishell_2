/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/08 21:37:35 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/08 21:37:36 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	dup_pipe_and_exec(t_all *all, int *fd, char **av, int dup)
{
	if (dup == 1)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(create_good_path(all, av), av, all->dupenv);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(create_good_path(all, av), av, all->dupenv);
	}
}

void	exec_pipe(t_all *all)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	int		save = 0;

	i = 0;
	while (all->pipe[i])
	{
		if (pipe(fd) == -1)
			error("PIPE");
		if ((pid = fork()) == -1)
			error("FORK");
		else if (pid == 0)
		{
			if (all->pipe[i + 1])
			{
				all->pipe[i] = ft_epur_str(all->pipe[i]);
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[i], ' '), 1);
				exit(0);
			}
			else
			{
				all->pipe[i] = ft_epur_str(all->pipe[i]);
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[i], ' '), 0);
				exit(0);
			}
		}
		else
		{
			if (all->pipe[i + 1])
			{
				all->pipe[i + 1] = ft_epur_str(all->pipe[i + 1]);
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[i + 1], ' '), 0);
				exit(0);
			}
		}
		i = i + 2;
	}
}

void	extended_create_pipe(t_all *all, char **dup, int ct)
{
	int		i;

	i = 0;
	if (all->pipe != NULL)
		del_array(&all->pipe);
	all->pipe = (char **)malloc(sizeof(char*) * 2 + 1);
	while (i < 2 && dup[ct] != NULL)
		all->pipe[i++] = ft_strdup(dup[ct++]);
	all->pipe[i] = NULL;
}

void	create_pipe(t_all *all)
{
	pid_t	pid;
	char	**tmp;
	int		len;

	pid = 0;
	tmp = ft_strsplit(all->cmd, '|');
	len = ft_tablen(tmp);
	if ((len % 2) != 0)
		extended_create_pipe(all, tmp, len - 1);
	else
		extended_create_pipe(all, tmp, len - 2);
	if ((pid = fork()) == -1)
		error("FORK");
	else if (pid == 0)
	{
		exec_pipe(all);
		exit(0);
	}
	else
		wait(NULL);
}
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
	int		nb_pipe = 0;

	if (all->pipe)
	{
		if (pipe(fd) == -1)
			error("PIPE");
		if ((pid = fork()) == -1)
			error("FORK");
		else if (pid == 0)
		{
			if (all->pipe[nb_pipe + 1])
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[nb_pipe], ' '), 1);
			else
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[nb_pipe], ' '), 0);
			exit(0);
		}
		else
		{
			if (all->pipe[nb_pipe + 1])
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[nb_pipe + 1], ' '), 0);
			exit(0);
		}
	}
}

void	extended_create_pipe(t_all *all, char **dup, int ct, int len)
{
	int		i;

	i = 0;
	if (all->pipe != NULL)
		del_array(&all->pipe);
	all->pipe = (char **)malloc(sizeof(char*) * len + 1);
	while (i < len && dup[ct] != NULL)
		all->pipe[i++] = ft_epur_str(dup[ct++]);
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
	extended_create_pipe(all, tmp, 0, len);
	// if (len > 2)
	// 	exec_multi_pipe(all, len);
	// else
	// {
		if ((pid = fork()) == -1)
			error("FORK");
		else if (pid == 0)
		{
			exec_pipe(all);
			exit(0);
		}
		else if (pid > 0)
			wait(NULL);
}

// void	exec_multi_pipe(t_all *all, int len)
// {
// 	pid_t	pid;
// 	int		fds[len * 2];
// 	int		nb_cmd = 0;
// 	int		i = 0;
// 	char	**av;

// 	while (i < len)
// 		pipe(fds);
// 	av = NULL;
// 	i = 0;
// 	while (all->pipe[i])
// 	{
// 		if ((pid = fork()) == -1)
// 			error("FORK");
// 		else if (pid == 0)
// 		{
// 			if (all->pipe[i])
// 				dup2(fds[nb_cmd - 1 * 2], 0);
// 			else if (all->pipe[i + 1])
// 				dup2(fds[nb_cmd * 2 + 1], 1);
// 			while (len * 2)
// 				close(fds[nb_cmd]);
// 			if (av != NULL)
// 				del_array(&av);
// 			av = ft_strsplit(all->pipe[i], ' ');
// 			execve(create_good_path(all, av), av, all->dupenv);
// 			exit(0);
// 		}
// 		else
// 		{
// 			i++;
// 			nb_cmd++;
// 		}
// 	}
// }



















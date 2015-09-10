/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 23:29:15 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/02 09:11:05 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	erase_and_replace(t_all *all)
{
	char	**argv;
	int		dupstdout;
	char	*tmp;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '>');
	tmp = ft_epur_str(all->redirection[1]);
	if ((all->fd2open = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		shell_error("OPEN", all->redirection[1]);
	ft_strdel(&tmp);
	argv = ft_strsplit(all->redirection[0], ' ');
	dupstdout = dup(STDOUT_FILENO);
	dup_and_exec(all, argv, dupstdout, STDOUT_FILENO);
}

void	add_to_end(t_all *all)
{
	char	**argv;
	int		dupstdout;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '>');
	all->redirection[1] = ft_epur_str(all->redirection[1 + 1]);
	if ((all->fd2open = open(all->redirection[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		shell_error("OPEN", all->redirection[1]);
	all->redirection[0] = ft_epur_str(all->redirection[0]);
	argv = ft_strsplit(all->redirection[0], ' ');
	dupstdout = dup(STDOUT_FILENO);
	dup_and_exec(all, argv, dupstdout, STDOUT_FILENO);
}

void	read_file(t_all *all)
{
	char	**argv;
	int		dupstdin;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '<');
	all->redirection[1] = ft_epur_str(all->redirection[1]);
	if ((all->fd2open = open(all->redirection[1], O_RDONLY)) == -1)
		shell_error("OPEN", all->redirection[1]);
	argv = ft_strsplit(all->redirection[0], ' ');
	dupstdin = dup(0);
	dup_and_exec(all, argv, dupstdin, STDIN_FILENO);
}

void	read_stdin(t_all *all)
{
	printf("read_stdin: %s\n", all->cmd);
	// char	**argv;
	// int		dupstdin;

	// argv = NULL;
	// all->redirection = ft_strsplit(all->cmd, '<');
	// all->redirection[1] = ft_epur_str(all->redirection[1 + 1]);
	// if ((all->fd2open = open(all->redirection[1], O_RDONLY)) == -1)
	// 	shell_error("OPEN", all->redirection[1]);
	// argv = ft_strsplit(all->redirection[0], ' ');
	// dupstdin = dup(0);
	// dup_and_exec(all, argv, dupstdin, STDIN_FILENO);
}




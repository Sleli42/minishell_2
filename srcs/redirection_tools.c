/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 09:42:54 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/03 09:42:56 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		check_redirection(char *cmd)
{
	if (cmd && *cmd)
	{
		while (*cmd)
		{
			if (*cmd == '>' || *cmd == '<' || *cmd == '|'
				|| (*cmd == '>' && (*cmd +1) == '>')
				|| (*cmd == '<' && (*cmd +1) == '<'))
				return (1);
			cmd++;
		}
	}
	return (0);
}

void	dup_and_exec(t_all *all, char **argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&argv);
	del_array(&all->redirection);
}

/* ====================================================

if (father)
	{
		close(fd[1]);
		save = dup(0);
		dup2(fd[0], 0);
		ft_seek_tree(tree->right, e);
		close(fd[0]);
		dup2(save, 0);
		wait(&father);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_seek_tree(tree->left, e);
		close(fd[1]);
		exit(0);
	}

 						==================================================== */
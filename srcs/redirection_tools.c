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

char		*create_good_path(t_all *all, char **argv_bin)
{
	int		ct = 0;
	char	*bin_tmp;

	bin_tmp = NULL;
	while (all->path2exec[ct])
	{
		bin_tmp = create_path(all->path2exec[ct], argv_bin[0]);
		if (good_access(bin_tmp))
			return (bin_tmp);
		ft_strdel(&bin_tmp);
		ct++;
	}
	return (NULL);
}

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
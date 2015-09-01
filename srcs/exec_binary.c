/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 22:03:11 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/01 08:19:34 by sleli42          ###   ########.fr       */
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

void	choose_dup(t_all *all)
{
	//write(1, "before\n", 7);
	if (all->redir_name == SRD)
	{
		//printf("redir name: %d\n", all->redir_name);
		if (!(all->fd2open = dup(STDOUT_FILENO)))
			error("DUP2");
	}
	//write(1, "after\n", 6);
	//else if (all->redir_name == SRG)
	//	dup2(STDOUT_FILENO, all->fd2read);
}

void	exec_right_binary(t_all *all, char **argv_bin)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	// display_tab(all->path2exec);
	// display_tab(argv_bin);
	// exit(1);
	while (all->path2exec[ct])
	{
		bin_tmp = create_path(all->path2exec[ct], argv_bin[0]);
	//	printf("%s\n", bin_tmp);
		if (good_access(bin_tmp))
		{
		//	write(1, "good access\n", 13);
			if (all->redir_name != R_NULL)
				choose_dup(all);
			//write(1, "before\n", 7);
			exec_binary(bin_tmp, argv_bin, all->dupenv);
			//write(1, "after\n", 6);
		}
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
		ft_putendl("No child process");
	if (pid == 0)
		if (execve(bin, argv_bin, env) == -1)
			error("EXECVE");
	if (pid > 0)
		waitpid(pid, &buff, 0);
}

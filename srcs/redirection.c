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

/* =======================================================
*** '>' simple chevron fermant, redirige la sortie de la commande dans un fichier.
*** si le fichier n'existe pas, il faut le creer
*** si le fichier existe, le remplace.
***
*** '>>' double chevron fermant, redirige le resultat, mais a la fin d'un fichier.
*** si le fichier n'existe pas, il faut le creer
*** si le fichier exite, ecrit a la fin.
***
*** '<' envoie un contenu d'un fichier, dans le binaire
*** (ex: cat < file == cat file)
*** sauf qu'il ne l'open pas, il se contente de l'afficher.
*** '<<' lit depuis le clavier progressivement,
*** (ex: wc << strstop) la string strstop, est la condition d'arret
*** on peut alors ecrire : > "string 1"
***						   > "string 2 ..."
*** 					   > "strstop"
***	le programme renvoie le resultat de wc,
*** des deux chaines passer en parametre progressivement.
***
*** '|' permet de chainer les commandes,
*** tout ce qui sort de la commande1 est immédiatement envoyé à la commande2 ect...
*** "echo lulu > auteur | cat auteur | echo lulu >> auteur | cat -e auteur"
*** ==		$> lulu$
***			$> lulu$
*** cat auteur n'est pas exec, car il y a encore des actions a faire sur ce fichier.
*** "echo lulu > auteur | cat auteur | echo lulu >> auteur2 | cat -e auteur2"
*** ==		$> lulu$
*** n'execute toujours pas le 1er cat, il execute uniquement le dernier bin.


*** int dup2(int oldfd, int newfd);
*** dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd
       si besoin est, mais prenez note des points suivants.
 				      ======================================================= */

static char		*create_good_path(t_all *all, char **argv_bin)
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
			}
			else
			{
				all->pipe[i] = ft_epur_str(all->pipe[i]);
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[i], ' '), 0);
			}
			exit(0);
		}
		else
		{
			if (all->pipe[i + 1])
			{
				all->pipe[i + 1] = ft_epur_str(all->pipe[i + 1]);
				dup_pipe_and_exec(all, fd, ft_strsplit(all->pipe[i + 1], ' '), 0);
			}
			exit(0);
		}
		i = i + 2;
	}
}

void	create_pipe(t_all *all)
{
	pid_t	pid;

	pid = 0;
	all->pipe = ft_strsplit(all->cmd, '|');
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

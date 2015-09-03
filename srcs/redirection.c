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

       	/* no works ... */

void	create_pipe(t_all *all)
{
	char	**argv;
	pid_t	pid;
	int		fd[2];
	int		dupfd;

	all->redirection = ft_strsplit(all->cmd, '|');
	pipe(fd);
	pid = fork();
	if (pid)
	{
		dupfd = dup(STDIN_FILENO);
		close(fd[STDOUT_FILENO]);
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		all->redirection[0] = ft_epur_str(all->redirection[0]);
		argv = ft_strsplit(all->redirection[0], ' ');
		exec_right_binary(all, argv);
		close(fd[STDIN_FILENO]);
		dup2(dupfd, STDIN_FILENO);
		wait(&pid);
	}
	else
	{
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		del_array(&argv);
		all->redirection[1] = ft_epur_str(all->redirection[1]);
		argv = ft_strsplit(all->redirection[1], ' ');
		exec_right_binary(all, argv);
		close(fd[STDOUT_FILENO]);
		exit (0);
	}
}

			/* no works ... */

void	erase_and_replace(t_all *all)
{
	char	**argv;
	int		dupstdout;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '>');
	all->redirection[1] = ft_epur_str(all->redirection[1]);
	if ((all->fd2open = open(all->redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		shell_error("OPEN", all->redirection[1]);
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

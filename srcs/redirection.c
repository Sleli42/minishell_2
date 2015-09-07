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

// void	create_pipe(t_all *all)
// {
// 	char	**argv;
// 	pid_t	pid;
// 	int		fd[2];
// 	int		dupfd;

// 	all->redirection = ft_strsplit(all->cmd, '|');
// 	pipe(fd);
// 	pid = fork();
// 	if (pid)
// 	{
// 		dupfd = dup(STDIN_FILENO);
// 		close(fd[STDOUT_FILENO]);
// 		dup2(fd[STDIN_FILENO], STDIN_FILENO);
// 		all->redirection[0] = ft_epur_str(all->redirection[0]);
// 		argv = ft_strsplit(all->redirection[0], ' ');
// 		exec_right_binary(all, argv);
// 		close(fd[STDIN_FILENO]);
// 		dup2(dupfd, STDIN_FILENO);
// 		wait(&pid);
// 	}
// 	else
// 	{
// 		close(fd[STDIN_FILENO]);
// 		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
// 		del_array(&argv);
// 		all->redirection[1] = ft_epur_str(all->redirection[1]);
// 		argv = ft_strsplit(all->redirection[1], ' ');
// 		exec_right_binary(all, argv);
// 		close(fd[STDOUT_FILENO]);
// 		exit (0);
// 	}
// }

// void	create_pipe(t_all *all)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	char	*cmd2exec;
// 	char	**argv;
// //	int		save = 0;

// 	pipe(fd);
// 	pid = fork();
// 	all->redirection = ft_strsplit(all->cmd, '|');
// 	if (pid == 0)	/*child*/
// 	{
// 		all->redirection[0] = ft_epur_str(all->redirection[0]);
// 		argv = ft_strsplit(all->redirection[0], ' ');
// 		// cmd2exec = create_good_path(all ,argv);
// 		close(fd[1]);
// 		//save = dup(0);
// 		dup2(fd[0], 0);
// 		// dup2(fd[1], STDOUT_FILENO);
// 		execve(cmd2exec, argv, all->dupenv);
// 		close(fd[0]);
// 		// dup2(save, 0);
// 		// wait(&pid);
// 		del_array(&argv);
// 		del_array(&all->redirection);
// 	}
// 	else
// 	{
// 		// pid = fork();
// 		// if (pid == 0)	/*father*/
// 		// {
// 			all->redirection[1] = ft_epur_str(all->redirection[1]);
// 			argv = ft_strsplit(all->redirection[1], ' ');
// 			//cmd2exec = create_good_path(all ,argv);
// 			close(fd[0]);
// 			dup2(fd[1], 1);
// 			execve(cmd2exec, argv, all->dupenv);
// 			close(fd[1]);
// 			del_array(&argv);
// 			del_array(&all->redirection);
// 		//}
// 	}
// }

			/* no works ... */
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

// static void	exec_child(t_all *all, char **argv, int *fd)
// {
// 	//pid_t	child;

// 	close(fd[1]);
// 	dup2(fd[0], 0);
// 	close(fd[0]);
// 	//child = fork();
// 	//if (child > 0)
// 	//	wait(NULL);
// 	//if (child == 0)
// 		execve(create_good_path(all, argv), argv, all->dupenv);
// }

// static void	exec_father(t_all *all, char **argv, int *fd)
// {
// 	pid_t	father;

// 	close(fd[0]);
// 	dup2(fd[1], 1);
// 	close(fd[1]);
// 	father = fork();
// 	if (father > 0)
// 		wait(NULL);
// 	if (father == 0)
// 		execve(create_good_path(all, argv), argv, all->dupenv);
// }

void	exec_process(t_all *all, char **argv)
{
	char	*bin;
	int		buff;
	pid_t	pid;

	bin = create_good_path(all, argv);
	pid = fork();
	if ((!pid))
	{
		execve(bin, argv, all->dupenv);
		ft_strdel(&bin);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &buff, 0);
}

void	create_pipe(t_all *all)
{
	int		fd[2];
	pid_t	pid;
	char	**argv1;
	char	**argv2;
	int		save = 0;
	// int		save2 = 0;

	//save1 = dup(0);
	pipe(fd);
	pid = fork();
	all->redirection = ft_strsplit(all->cmd, '|');
	all->redirection[0] = ft_epur_str(all->redirection[0]);
	argv1 = ft_strsplit(all->redirection[0], ' ');
	all->redirection[1] = ft_epur_str(all->redirection[1]);
	argv2 = ft_strsplit(all->redirection[1], ' ');
	//display_tab(argv2);
	//exit(1);
	// save = dup(1);
	// save2 = dup(0);
	save = dup(1);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(create_good_path(all, argv2), argv2, all->dupenv);
		exit(0);
	}
	else
	{
		pid_t pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			execve(create_good_path(all, argv1), argv1, all->dupenv);
			exit(0);
		}
		else
		{
			dup2(save, 1);
			close(save);
			waitpid(pid2, NULL, 0);
		}
		//write(1, "first2\n", 7);
		//buff = execve(create_good_path(all, argv1), argv1, all->dupenv);
		//waitpid(pid, &buff, 0);
		//waitpid(pid, NULL, 0);
	}
	// dup2(save2, 0);
	// dup2(save, 1);
	// close(save);
	// close(save2);
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

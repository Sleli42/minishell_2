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

int		check_redirection(char *cmd)
{
	if (cmd && *cmd)
	{
		while (*cmd)
		{
			if (*cmd == '>' || *cmd == '<'
				|| (*cmd == '>' && (*cmd +1) == '>')
				|| (*cmd == '<' && (*cmd +1) == '<'))
				return (1);
			cmd++;
		}
	}
	return (0);
}

void	erase_and_replace(t_all *all)
{
	char	**argv;
	int		dupstdout;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '>');
	all->redirection[1] = ft_epur_str(all->redirection[1]);
	if (!(all->fd2open = open(all->redirection[1], (O_WRONLY | O_CREAT | O_TRUNC), 0644)))
		printf("open error \n");
	argv = ft_strsplit(all->redirection[0], ' ');
	dupstdout = dup(STDOUT_FILENO);
	dup2(all->fd2open, STDOUT_FILENO);
	close(all->fd2open);
	exec_right_binary(all, argv);
	dup2(dupstdout, STDOUT_FILENO);
	close(dupstdout);
	del_array(&argv);
	del_array(&all->redirection);
}

void	add_to_end(t_all *all)
{
	printf("addtoend |%s|\n", all->cmd);
}

void	read_file(t_all *all)
{
	printf("readfile |%s|\n", all->cmd);
	/*
	char	**argv;

	argv = NULL;
	all->redirection = ft_strsplit(all->cmd, '<');
	all->redirection[1] = ft_epur_str(all->redirection[1]);
	if (!(all->fd2read = open(all->redirection[1], (O_WRONLY | O_TRUNC | O_APPEND),  0644)))
		printf("open error \n");
	if (all->redirection[0][ft_strlen(all->redirection[0]) - 1] == ' ')
		all->redirection[0][ft_strlen(all->redirection[0]) - 1] = '\0';
	argv = ft_strsplit(all->redirection[0], ' ');
	all->redir_name = SRG;
	exec_right_binary(all, argv);
	del_array(&argv);
	del_array(&all->redirection);
	close(all->fd2open);
	*/
}

void	read_stdin(t_all *all)
{
	printf("readstdin |%s|\n", all->cmd);
}

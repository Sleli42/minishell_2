/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/27 23:29:15 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/29 05:16:31 by lubaujar         ###   ########.fr       */
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
	printf("erasenreplace |%s|\n", all->cmd);
	printf("redirect_cmd : %s\n", all->redirect_cmd);
	all->redirection = my_split(all->cmd, ' ');
	write(1, "segfault\n", 9);
	display_tab(all->redirection);
	exit(1);
}

void	add_to_end(t_all *all)
{
	printf("addtoend |%s|\n", all->cmd);
}

void	read_file(t_all *all)
{
	printf("readfile |%s|\n", all->cmd);
}

void	read_stdin(t_all *all)
{
	printf("readstdin |%s|\n", all->cmd);
}

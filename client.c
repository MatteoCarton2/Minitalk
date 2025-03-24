/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:25 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/24 19:43:29 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// SIGUSR1 = 0
// SIGUSR2 = 1

// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!

// SI j'enlève les if kill == -1 je dois changer int send_message par void et enlever le return 0 !!

int	send_message(pid_t pid, char *str)
{
	int	i;
    int bit;

	i = 0;
	while (*str)
	{
        i = 7;
		while (i >= 0)
		{
            // D'abord, on crée un masque avec 1 << i
            // Ensuite on fait un "&" avec notre caractère.
            // Exemple : 
            // Caractère 'A': 01000001
            // Masque (i = 7): 10000000
            // ----------------------
            // Résultat:       00000000
            // car Si les deux bits sont 1 → résultat 1, Sinon → résultat 0
            bit = (*str & (1 << i));
            if (bit == 0)
            {
                if (kill (pid, SIGUSR1) == -1) // kill = fct qui envoie un message
                {
                    printf ("Error KILL\n");
                    return (1);
                }
            }
            else
            {
                if (kill (pid, SIGUSR2) == -1)
                {
                    printf ("Error KILL\n");
                    return (1);
                }
            }
            usleep(50);
            i--;
		}
        str++;
	}
    return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Wrong numbers of arguments !\n"); // UTILISER MON PROPRE PRINTF
		return (1);
	}
	pid_t pid;
	pid = ft_atoi(argv[1]);
    send_message(pid, argv[2]);
    send_message(pid, "\0");  // Envoi du caractère nul pour déclencher l'affichage
    return (0);
}
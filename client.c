/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:53 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/24 20:11:07 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
                    ft_printf("Error KILL\n");
                    return (1);
                }
            }
            else
            {
                if (kill (pid, SIGUSR2) == -1)
                {
                    ft_printf("Error KILL\n");
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
		ft_printf("Wrong numbers of arguments !\n"); // UTILISER MON PROPRE PRINTF
		return (1);
	}
	pid_t pid;
	pid = ft_atoi(argv[1]);
    send_message(pid, argv[2]);
    
    // Envoi du caractère nul manuellement
    int i = 7;
    while (i >= 0)
    {
        if (kill(pid, SIGUSR1) == -1) // Caractère nul = tous les bits à 0
        {
            ft_printf("Error KILL\n");
            return (1);
        }
        usleep(50);
        i--;
    }
    
    return (0);
}
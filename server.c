/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/24 20:03:57 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!
// CHANGER TOUS LES PRINTF PAR FT_PRINTF !!!

// METTRE LES STATIC

// GERER LES FREE

static t_server g_server;

static int check_memory(void) {

    char *temp;

    if (g_server.size - g_server.char_pos <= 3)
    {
        temp = malloc(sizeof(char) * (g_server.size * 2));
        if (temp == NULL)
            return (1);
        /*ft_memcpy prend 3 paramètres :
La destination (où on veut copier) : temp
La source (d'où on copie) : g_server.str
Le nombre d'octets à copier : g_server.char_pos*/
        ft_memcpy(temp, g_server.str, g_server.char_pos);
        free(g_server.str); // on libère l'ancien contenu
        g_server.str = temp; // on fais pointer g_server.str vers la nouvelle mémoire
        g_server.size *= 2; // on met à jour la taille
    }
    return (0);
}

static int init_server(void) {
    g_server.str = malloc(sizeof(char) * 32);
    if (g_server.str == NULL)
    {
        ft_printf("Erreur malloc\n");
        return (1);
    }
    g_server.char_bits = 0;
    g_server.c = 0;
    g_server.char_pos = 0;
    g_server.size = 32; // taille initiale au hasard
    return (0);
}


static void handle_signal (int sig) {
    if (sig == SIGUSR1) // = 0
    {
        // printf("Reçu SIGUSR1 (0) - Position bit: %d\n", g_server.char_bits);
        // g_server.c &= ~(1 << (7 - g_server.char_bits));
        g_server.char_bits++;
    }
    if (sig == SIGUSR2) // = 1
    {
        // printf("Reçu SIGUSR2 (1) - Position bit: %d\n", g_server.char_bits);
        g_server.c |= (1 << (7 - g_server.char_bits));
        g_server.char_bits++;
    }
        
    if (g_server.char_bits == 8)
    {
        // printf("Caractère complet reçu: %c (ASCII: %d)\n", g_server.c, g_server.c);
        // on check si il y'a de la place avant de stocker un charactère
        if (check_memory() == 1)
            return;
        /* Quand on a un caractère complet, on le stocke dans notre chaîne (g_server.str)
        À la bonne position (g_server.char_pos)*/
        g_server.str[g_server.char_pos] = g_server.c;
        g_server.char_pos++;
        
        // si on reçoit le caractère nul, c'est la fin de la chaîne
        if (g_server.c == '\0')
        {
            // Debug pour confirmer réception du caractère nul
            // printf("CARACTÈRE NUL DÉTECTÉ - FIN DE CHAÎNE!\n");
            // Afficher la chaîne complète
            // printf("Message reçu : %s\n", g_server.str);
            //printf("Longueur du message: %d caractères\n", g_server.char_pos - 1);
            ft_printf("%s\n", g_server.str);
            // réinitialiser pour la prochaine chaîne
            g_server.char_pos = 0;
            free(g_server.str);
            init_server();
        }
        
        g_server.c = 0;
        g_server.char_bits = 0;
    }
}

int main() {
    ft_printf("Server PID = %d\n", getpid());
    if (init_server() == 1)
        return (1);
    
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (42)
        pause();
    
    
    return (0);
}
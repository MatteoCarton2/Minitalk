/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/24 19:23:08 by mcarton          ###   ########.fr       */
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
        printf("Erreur malloc\n");
        return (1);
    }
    g_server.char_bits = 0;
    g_server.c = 0;
    g_server.char_pos = 0;
    g_server.size = 32; // taille initiale au hasard
    return (0);
}

static void display_and_reset() {
    printf("%s", g_server.str);
    g_server.char_pos = 0;
    g_server.c = 0;
    g_server.char_bits = 0;
    g_server.str[0] = '\0';
}

static void handle_signal (int sig) {
    if (sig == SIGUSR1) // = 0
    {
        g_server.char_bits++;
    }
    if (sig == SIGUSR2) // = 1
    {
        /* Imagine que tu as 8 positions : 7 6 5 4 3 2 1 0
Si g_server.char_bits = 0 :
7 - 0 = 7
1 << 7 donne : 10000000
Si g_server.char_bits = 1 :
7 - 1 = 6
1 << 6 donne : 01000000*/
        /*Explication de "|="
Ok, imaginons que tu joues avec des Lego !
Tu as une ligne de 8 briques Lego :
Une brique blanche = 0
Une brique rouge = 1
Au début, toutes tes briques sont blanches :
Apply to server.c
⬜⬜⬜⬜⬜⬜⬜⬜
Le symbole |= c'est comme une règle de jeu qui dit :
"Tu peux ajouter des briques rouges, mais tu ne peux JAMAIS enlever ou remplacer une brique rouge"
Par exemple, si tu veux mettre une brique rouge à la deuxième position :
Avant : ⬜⬜⬜⬜⬜⬜⬜⬜
Après : ⬜🟥⬜⬜⬜⬜⬜⬜
Si plus tard tu veux ajouter une autre brique rouge :
Les briques rouges déjà placées restent
Tu ajoutes juste ta nouvelle brique rouge
C'est exactement ce que fait |= dans notre code :
Il garde tous les 1 qu'on a déjà mis
Il ajoute un nouveau 1 où on veut
Il ne touche pas aux 0*/
        g_server.c |= (1 << (7 - g_server.char_bits));
        g_server.char_bits++;
    }
        
    if (g_server.char_bits == 8)
        {
            // on check si il y'a de la place avant de stocker un charactère
            if (check_memory() == 1)
                return;
            /* Quand on a un caractère complet, on le stocke dans notre chaîne (g_server.str)
            À la bonne position (g_server.char_pos)*/
            g_server.str[g_server.char_pos] = g_server.c;
            g_server.char_pos++;
            if (g_server.c == '\0')
                display_and_reset();
            g_server.c = 0;
            g_server.char_bits = 0;
        }
}

int main() {
    printf("Server PID = %d\n", getpid());
    if (init_server() == 1)
        return (1);
    
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (42)
        pause();
    
    
    return (0);
}
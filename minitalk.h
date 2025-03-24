/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:36 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/24 17:19:22 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/* Cette structure nous permet de :
Stocker la chaîne en cours de réception (str)
Savoir où on en est dans la construction du caractère actuel (char_bits)
Savoir où placer le prochain caractère (char_pos)
Gérer la réallocation quand nécessaire (size) */

typedef struct s_server {
    char    *str;       // La chaîne en cours de réception (allocation dynamique)
    char    c;          // Le charactère en construction
    int     char_bits;  // Bits reçus pour le caractère en cours (0-7)
    int     char_pos;   // Position dans la chaîne
    int     size;       // Taille totale allouée
} t_server;

#endif


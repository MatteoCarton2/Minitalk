/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 10:45:03 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server	g_server;

static int	check_memory(void)
{
	char	*temp;

	if (g_server.size - g_server.char_pos <= 3)
	{
		temp = malloc(sizeof(char) * (g_server.size * 2));
		if (temp == NULL)
			return (1);
		ft_memcpy(temp, g_server.str, g_server.char_pos);
		free(g_server.str);
		g_server.str = temp;
		g_server.size *= 2;
	}
	return (0);
}

static int	init_server(void)
{
	g_server.str = malloc(sizeof(char) * 32);
	if (g_server.str == NULL)
	{
		ft_printf("Erreur malloc\n");
		return (1);
	}
	g_server.char_bits = 0;
	g_server.c = 0;
	g_server.char_pos = 0;
	g_server.size = 32;
	return (0);
}

static void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
		g_server.char_bits++;
	if (sig == SIGUSR2)
	{
		g_server.c |= (1 << (7 - g_server.char_bits));
		g_server.char_bits++;
	}
	if (g_server.char_bits == 8)
	{
		if (check_memory() == 1)
			return ;
		g_server.str[g_server.char_pos] = g_server.c;
		g_server.char_pos++;
		if (g_server.c == '\0')
		{
			ft_printf("%s\n", g_server.str);
			free(g_server.str);
			init_server();
		}
		g_server.c = 0;
		g_server.char_bits = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID = %d\n", getpid());
	if (init_server() == 1)
		return (1);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (42)
		pause();
	return (0);
}

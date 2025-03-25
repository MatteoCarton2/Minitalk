/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:06:53 by mcarton           #+#    #+#             */
/*   Updated: 2025/03/25 10:50:10 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(pid_t pid, char *str)
{
	int	i;
	int	bit;

	i = 0;
	while (*str)
	{
		i = 7;
		while (i >= 0)
		{
			bit = (*str & (1 << i));
			if (bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(200);
			i--;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		ft_printf("Wrong numbers of arguments !\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	i = 7;
	while (i >= 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf("Error KILL\n");
			return (1);
		}
		usleep(50);
		i--;
	}
	return (0);
}

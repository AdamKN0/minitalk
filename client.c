/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:48:42 by kadam             #+#    #+#             */
/*   Updated: 2024/04/04 20:05:08 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_print_bit(unsigned char octet, int pid)
{
	int	i;
	int	x;

	i = 128;
	x = 0;
	while (i > 0)
	{
		if (octet >= i)
		{
			octet = octet - i;
			x = kill(pid, SIGUSR1);
			if (x == -1)
				ft_print_error("Error :\nin kill\n");
		}
		else
		{
			x = kill(pid, SIGUSR2);
			if (x == -1)
				ft_print_error("Error :\nin kill\n");
		}
		i = i / 2;
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac != 3)
		ft_print_error("Error :\nInvalid number of arguments\n");
	else
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			ft_print_error("Error :\nInvalid PID\n");
		while (av[2][i] != '\0')
		{
			ft_print_bit(av[2][i], pid);
			i++;
		}
	}
	return (0);
}

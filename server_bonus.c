/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:45:56 by kadam             #+#    #+#             */
/*   Updated: 2024/04/04 20:06:35 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int			g_pid;

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

static char	ft_convert_bits_to_char(const char *str)
{
	int				i;
	unsigned char	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		c = c * 2 + str[i] - '0';
		i++;
	}
	write(1, &c, 1);
	return (c);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	char_buffer[9];
	static int	i;
	char		c;

	(void)context;
	if (g_pid == 0)
		g_pid = info->si_pid;
	else if (g_pid > 0 && g_pid != info->si_pid)
	{
		i = 0;
		g_pid = info->si_pid;
	}
	if (signum == SIGUSR1)
		char_buffer[i++] = '1';
	else if (signum == SIGUSR2)
		char_buffer[i++] = '0';
	if (i == 8)
	{
		char_buffer[8] = '\0';
		i = 0;
		c = ft_convert_bits_to_char(char_buffer);
		ft_bzero(char_buffer, 9);
		if (c == '\0')
			kill(g_pid, SIGUSR2);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;
	int					x;
	int					y;

	pid = getpid();
	if (pid <= 0)
		ft_print_error("Error :\nInvalid PID\n");
	write(1, "PID: ", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	x = sigaction(SIGUSR1, &sa, NULL);
	y = sigaction(SIGUSR2, &sa, NULL);
	if (x == -1 || y == -1)
		ft_print_error("Error :\nin sigaction\n");
	while (1)
		pause();
	return (0);
}

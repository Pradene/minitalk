/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:31:55 by lpradene          #+#    #+#             */
/*   Updated: 2023/01/19 19:44:34 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_received = 0;

void	handle_signal(int signal, siginfo_t *client, void *ucontext)
{
	(void)ucontext;
	(void)client;
	if (signal == SIGUSR1)
		g_received = 1;
	else
		write(1, "The server received the string\n", 31);
}

void	send_size(int pid, int size)
{
	int	i;

	i = -1;
	while (++i < 32)
	{
		g_received = 0;
		if (size & 0x01)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		if (!g_received)
			pause();
		size = size >> 1;
	}
}

void	send_char(int pid, unsigned char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		g_received = 0;
		if (c & 0x01)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		if (!g_received)
			pause();
		c = c >> 1;
	}
}

void	send_string(int pid, unsigned char *s)
{
	int	i;

	send_size(pid, ft_strlen(s));
	i = -1;
	while (s[++i])
		send_char(pid, s[i]);
	send_char(pid, 0);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	if (argc != 3)
	{
		write(1, "Invalid arguments : ./client PID STRING\n", 41);
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	if (pid <= 0)
		exit(EXIT_FAILURE);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handle_signal;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	send_string(pid, (unsigned char *)argv[2]);
	return (0);
}

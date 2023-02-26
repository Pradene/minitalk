/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:30:07 by lpradene          #+#    #+#             */
/*   Updated: 2023/01/19 19:31:10 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	getlen(int sig, unsigned char **str, int *received)
{
	static int	size = 0;
	static int	i = 0;

	if (sig == SIGUSR1)
		size |= 1 << i;
	i++;
	if (i == 32)
	{
		(*received) = 1;
		(*str) = malloc(sizeof(char) * (size + 1));
		(*str)[size] = 0;
		size = 0;
		i = 0;
		return ;
	}
}

void	print(int pid, unsigned char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	kill(pid, SIGUSR2);
	free(s);
}

void	handle_signal(int sig, siginfo_t *client, void *ucontext)
{
	static unsigned char	*str;
	static unsigned char	c = 0;
	static int				i = 0;
	static int				curr = 0;
	static int				received = 0;

	(void)ucontext;
	if (received)
	{
		if (i == 0)
			c = 0;
		if (sig == SIGUSR1)
			c |= 1 << i;
		i = (i + 1) % 8;
		if (c && i == 0)
			str[curr++] = c;
		else if (!c && i == 0)
			return ((void)(i = 0, curr = 0, received = 0,
				print(client->si_pid, str)));
	}
	else
		getlen(sig, &str, &received);
	kill(client->si_pid, SIGUSR1);
}

int	main(void)
{
	char				*s;
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handle_signal;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	s = ft_itoa(getpid());
	if (!s)
		exit(EXIT_FAILURE);
	write(1, s, ft_strlen((unsigned char *)s));
	write(1, "\n", 1);
	free(s);
	while (1)
		pause();
}

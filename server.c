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

#include "server.h"

int	pow_2(int n)
{
	int	nb;

	if (n == 0)
		return (1);
	nb = 2;
	while (--n)
		nb *= 2;
	return (nb);
}

void	getlen(int sig, unsigned char **str, int *received)
{
	static int	size = 0;
	static int	i = 0;

	if (sig == SIGUSR1)
		size += pow_2(i);
	if (i == 31)
	{
		*received = 1;
		*str = malloc(size + 1);
		(*str)[size] = 0;
		size = 0;
		i = 0;
		return ;
	}
	i++;
}

void	print(int pid, unsigned char *s)
{
	printf("%s\n", s);
	free(s);
	kill(pid, SIGUSR2);
}

void	handle_signal(int sig, siginfo_t *client, void *ucontext)
{
	static unsigned char	*str;
	static unsigned char	c = 0;
	static int				i = 8;
	static int				curr = 0;
	static int				received = 0;

	(void)ucontext;
	if (!received)
		getlen(sig, &str, &received);
	else
	{
		if (i < 0)
			c = 0;
		if (i < 0)
			i = 8;
		if (sig == SIGUSR1)
			c += pow_2(i);
		i--;
		if (c && i < 0)
			str[curr++] = c;
		else if (!c && i < 0)
		{
			i = 8;
			curr = 0;
			received = 0;
			print(client->si_pid, str);
		}
	}
	kill(client->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handle_signal;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	pid = getpid();
	printf("%d\n", pid);
	while (1)
		pause();
}

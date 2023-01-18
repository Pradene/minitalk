/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:39:15 by lpradene          #+#    #+#             */
/*   Updated: 2023/01/16 22:39:16 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int received = 0;

void    handle_signal(int signal, siginfo_t *client, void *ucontext)
{
    (void)ucontext;
    if (signal == SIGUSR1)
        received = 1;
    else
        exit(EXIT_FAILURE);
}

void    send_char(int pid, unsigned char c)
{
    int bit;

    bit = 1 << 8;
    while (bit)
    {
        received = 0;
        if (bit & c)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        if (!received)
            pause();
        bit = bit >> 1;
    }
}

void    send_string(int pid, unsigned char *s)
{
    int i;

    i = -1;
    while(s[++i])
        send_char(pid, s[i]);
    send_char(pid, 0);
}

int main(int argc, char **argv)
{
    int	                pid;
    struct sigaction    sig;

    if (argc != 3)
        return (0);
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = handle_signal;
    sigemptyset(&sig.sa_mask);
    sigaddset(&sig.sa_mask, SIGUSR1);
    sigaddset(&sig.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
	pid = atoi(argv[1]);
    if (pid < 0)
        return (0);
    send_string(pid, argv[2]);
    return (0);
}

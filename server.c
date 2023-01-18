/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:28:28 by lpradene          #+#    #+#             */
/*   Updated: 2023/01/16 22:28:30 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     pow_2(int n)
{
    int nb;

    if (n == 0)
        return (1);
    nb = 2;
    while (--n)
        nb *= 2;
    return (nb);
}

void    handle_signal(int sig, siginfo_t *client, void *ucontext)
{
    (void)ucontext;
    static unsigned char    c = 0;
    static int              i = 8;

    if (i < 0)
        c = 0;
    if (i < 0)
        i = 8;
    if (sig == SIGUSR1)
        c += pow_2(i);
    i--;
    if (c && i < 0)
        write(1, &c, 1);
    else if (!c && i < 0)
        kill(client->si_pid, SIGUSR2);
    kill(client->si_pid, SIGUSR1);
}

int main(void)
{
    int                 pid;
    struct sigaction    sig;

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

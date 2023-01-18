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

void    error(char *s)
{
    printf("%s\n", s);
    exit(EXIT_FAILURE);
}

void    handle_signal(int signal, siginfo_t *client, void *ucontext)
{
    (void)ucontext;
    if (signal == SIGUSR1)
        received = 1;
    else
        printf("The server received the string\n");
}

void    send_size(int pid, int size)
{
    int i;

    i = -1;
    while (++i < 32)
    {
        received = 0;
        if (size & 0x01)
        {
            if (kill(pid, SIGUSR1) == -1)
                error("Error");
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                error("Error");
        }
        if (!received)
            pause();
        size = size >> 1;
    }
}

void    send_char(int pid, unsigned char c)
{
    int bit;

    bit = 1 << 8;
    while (bit)
    {
        received = 0;
        if (bit & c)
        {
            if (kill(pid, SIGUSR1) == -1)
                error("Error");
        }
        else
        {
            if (kill(pid, SIGUSR2) == -1)
                error("Error");
        }
        if (!received)
            pause();
        bit = bit >> 1;
    }
}

void    send_string(int pid, unsigned char *s)
{
    int i;

    send_size(pid, strlen(s));
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
        error("You have to run the program with : ./client [PID] [STRING]");
    pid = atoi(argv[1]);
    if (pid <= 0)
        error("Invalid PID");
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = handle_signal;
    sigemptyset(&sig.sa_mask);
    sigaddset(&sig.sa_mask, SIGUSR1);
    sigaddset(&sig.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
    send_string(pid, argv[2]);
    return (0);
}

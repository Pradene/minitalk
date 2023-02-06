/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 03:02:19 by lpradene          #+#    #+#             */
/*   Updated: 2023/02/06 03:02:21 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	count(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*a;

	i = n;
	len = count(n);
	a = malloc(sizeof(char) + (len + 1));
	if (!a)
		return (NULL);
	a[len] = '\0';
	if (!n)
		a[0] = '0';
	while (i > 0)
	{
		--len;
		a[len] = i % 10 + '0';
		i = i / 10;
	}
	return (a);
}

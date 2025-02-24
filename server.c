/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:02:05 by tcarlier          #+#    #+#             */
/*   Updated: 2025/01/23 17:16:32 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

size_t	ft_strlen_safe(const char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
			len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const c)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen_safe(s1);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	str[i] = c;
	str[i + 1] = '\0';
	if (s1)
		free((char *)s1);
	return (str);
}

void	handler(int sig)
{
	static char	c = 0;
	static int	i = 0;
	static char	*str = NULL;

	if (sig == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		str = ft_strjoin(str, c);
		if (!str)
		{
			write(1, "Memory allocation error\n", 24);
			exit(1);
		}
		if (c == '\0')
		{
			write(1, str, ft_strlen_safe(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		c = 0;
		i = 0;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

#include "minitalk_bonus.h"

int	g_cpid;

unsigned char	get_char(char *s)
{
	int				pow;
	unsigned char	c;
	int				i;

	pow = 1;
	c = 0;
	i = 8;
	while (i-- > 0)
	{
		c += pow * (s[i] - '0');
		pow *= 2;
	}
	return (c);
}

void	ft_convert_bonus(char *s, siginfo_t *info, int *count)
{
	char			arr[5];
	unsigned char	c;

	c = get_char(s);
	if (c == 0)
	{
		*count = 0;
		ft_kill(info->si_pid, SIGUSR2);
		return ;
	}
	if ((c & (1 << 7)))
	{
		arr[(*count)++] = c;
		if (*count == 4)
		{
			write(1, arr, 4);
			*count = 0;
		}
	}
	else
		write(1, &c, 1);
}

void	handler_bn(int sig, siginfo_t *info, void *p)
{
	static int	i;
	static char	str[9];
	static int	count;

	(void)p;
	if (g_cpid != info->si_pid)
	{
		i = 0;
		count = 0;
		g_cpid = info->si_pid;
	}
	if (sig == SIGUSR1)
		str[i] = '0';
	else if (sig == SIGUSR2)
		str[i] = '1';
	i++;
	if (i == 8)
	{
		i = 0;
		str[8] = 0;
		ft_convert_bonus(str, info, &count);
	}
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "The server's process id is: ", 28);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler_bn;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

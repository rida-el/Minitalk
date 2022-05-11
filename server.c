#include "minitalk.h"

int g_cpid;

void ft_convert(char *s, siginfo_t *info)
{
	int pow;
	unsigned char c;
	int i;

	pow = 1;
	c = 0;
	i = 8;
	while (i-- > 0)
	{
		c += pow * (s[i] - '0');
		pow *= 2;
	}
	if (c == 0)
		ft_kill(info->si_pid, SIGUSR2);
	write(1, &c, 1);
}

void handler(int sig, siginfo_t *info, void *p)
{
	static int i;
	int j = 0;
	static char str[9];
	(void)p;
	if (g_cpid != info->si_pid)
	{
		i = 0;
		g_cpid = info->si_pid;
		while (str[j])
		{
			str[j] = '0';
			j++;
		}
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
		ft_convert(str, info);
	}
}

int main(void)
{
	struct sigaction sa;

	write(1, "The server's process id is: ", 28);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
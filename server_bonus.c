#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int g_cpid;
int fffd;

void ft_putnbr(long long n)
{
	char *base_ten;

	base_ten = "0123456789";
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &base_ten[n % 10], 1);
}

void ft_kill(int pid, int sig)
{
	int ret;

	ret = kill(pid, sig);
	if (ret == -1)
		exit(EXIT_FAILURE);
}

void ft_convert(char *s, siginfo_t *info, int *count)
{
	int pow;
	unsigned char c;
	int i;
	char arr[5];

	pow = 1;
	c = 0;
	i = 8;
	while (i-- > 0)
	{
		c += pow * (s[i] - '0');
		pow *= 2;
	}
	if (c == 0)
	{
		*count = 0;
		ft_kill(info->si_pid, SIGUSR2);
		return ;
	}
	if ((c & (1 << 7)) || *count != 0)
	{
		arr[(*count)++] = c;
		if (*count == 4)
		{
			write(1, arr, 4);
			*count = 0;
		}
	}
	else
	{
		write(1, &c, 1);
	}
}

void handler(int sig, siginfo_t *info, void *p)
{
	static int i;
	int j = 0;
	static char str[9];
	static int count;

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
		ft_convert(str, info, &count);
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
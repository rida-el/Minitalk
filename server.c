#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cpid;

void ft_putchar(char c)
{
	write(1, &c, 1);
}
void ft_putnbr(long long n)
{
	char *BASE_TEN;

	BASE_TEN = "0123456789";
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &BASE_TEN[n % 10], 1);
}
void ft_kill(int pid, int sig){
	int ret;

	ret = kill(pid, sig);
	if(ret == -1)
		exit(EXIT_FAILURE);
}
int abs(int n){
	if (n < 0){
		return (-n);
	}
	return (n);
}
void ft_convert(char *s, siginfo_t *info)
{
	int pow;
	unsigned int c;
	int i;

	pow = 1;
	c = 0;
	i = 8;
	while (i-- > 0)
	{
		c += pow * abs(s[i] - '0');
		pow *= 2;
	}
	// write(1, " c-->", 5);
	// ft_putnbr(c);
	if (c == 0)
	{
		ft_kill(info->si_pid, SIGUSR2);
	}
	write(1, &c, 1);
}

void handler(int sig, siginfo_t *info, void *p)
{
	static int i = 0;
	static char str[9];
	// char *str;

	if (cpid != info->si_pid)
	{
		i = 0;
		cpid = info->si_pid;
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

int main()
{
	struct sigaction sa;

	write(1, "The server's process id is: ", 28);
	ft_putnbr(getpid());
	ft_putchar('\n');

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
// 1011
// 0101
// 0001

// Algo
// client receives string as argument
// client reads string
// for erach character:
//		convert to bits
//		send each bit as signal
// server side:
//		server receives signals
//		server waits to receive 8 bits
//		server converts 8 bits to ASCII
//		server prints ASCII
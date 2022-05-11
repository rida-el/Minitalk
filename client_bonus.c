#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ft_kill(int pid, int sig)
{
	int ret;

	ret = kill(pid, sig);
	if (ret == -1)
		exit(EXIT_FAILURE);
}

void send_signal(int pid, unsigned char c)
{
	int bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & 128) == 0)
			ft_kill(pid, SIGUSR1);
		else
			ft_kill(pid, SIGUSR2);
		c = c << 1;
		bit++;
		usleep(300);
	}
}

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

void handler(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "ACKNOWLEDGED !\n", 15);
	}
}

int main(int argc, char **argv)
{
	int pid;
	int i;
	char *bit;

	if (argc != 3)
	{
		printf("Please input the PID and the string to send");
		return (0);
	}
	signal(SIGUSR2, handler);
	// signal(SIGINT, handle_int);
	pid = atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_signal(pid, (unsigned char)argv[2][i]);
		i++;
		// sleep(1);
	}
	send_signal(pid, (unsigned char)argv[2][i]);
}

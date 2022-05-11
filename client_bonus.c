#include "minitalk_bonus.h"

void send_signal_bn(int pid, unsigned char c)
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

	if (argc != 3)
	{
		printf("Please input the PID and the string to send");
		return (0);
	}
	signal(SIGUSR2, handler);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_signal_bn(pid, (unsigned char)argv[2][i]);
		i++;
	}
	send_signal_bn(pid, (unsigned char)argv[2][i]);
}

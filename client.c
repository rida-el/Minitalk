#include "minitalk.h"

void	send_signal(int pid, unsigned char c)
{
	int	bit;

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

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		write(1, "Please input the PID and the string to send", 43);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_signal(pid, (unsigned char)argv[2][i]);
		i++;
	}
}

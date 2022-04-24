#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}
void	ft_putnbr(long long n)
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

void    print_bits(unsigned char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		putchar((c & 128) ? '1' : '0');
		c = c << 1;
		bit++;
	}
	putchar('\n');
}

void handler(int sig)
{
	char c;

	if (sig == SIGUSR1){
		ft_putnbr(0);

	} else if (sig == SIGUSR2) {
		ft_putnbr(1);
	}

}


int main()
{
	ft_putnbr(getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	
	while(1){
		// ft_putchar('\n');
		pause();
	}
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
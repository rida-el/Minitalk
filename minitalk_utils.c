#include "minitalk.h"

void	ft_putnbr(long long n)
{
	char	*base_ten;

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

int	ft_atoi(const char *s1)
{
	int	i;
	int	signe;
	int	sum;
	int	v;

	i = 0;
	v = 0;
	sum = 0;
	signe = 1;
	while (s1[i] == ' ' || (s1[i] >= 9 && s1[i] <= 13))
		i++;
	while (s1[i] == '-' || s1[i] == '+' )
	{
		if (s1[i] == '-')
			signe = signe * -1;
		i++;
		v++;
	}
	if (v > 1)
		return (0);
	while (s1[i] >= '0' && s1[i] <= '9')
		sum = sum * 10 + s1[i++] - 48;
	return (sum * signe);
}

void	ft_kill(int pid, int sig)
{
	int	ret;

	ret = kill(pid, sig);
	if (ret == -1)
		exit(EXIT_FAILURE);
}

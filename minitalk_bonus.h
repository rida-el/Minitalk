#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>

void			ft_putnbr(long long n);
int				ft_atoi(const char *s1);
void			ft_kill(int pid, int sig);
void			send_signal_bn(int pid, unsigned char c);
void			handler(int sig);
unsigned char	get_char(char *s);
void			ft_convert_bonus(char *s, siginfo_t *info, int *count);
void			handler_bn(int sig, siginfo_t *info, void *p);

#endif

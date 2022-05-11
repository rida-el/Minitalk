#ifndef MINITALK_H
# define MINITALK_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ft_putnbr(long long n);
int	ft_atoi(const char *s1);
void ft_kill(int pid, int sig);
void ft_convert(char *s, siginfo_t *info);
void handler(int sig, siginfo_t *info, void *p);
void send_signal(int pid, unsigned char c);

#endif
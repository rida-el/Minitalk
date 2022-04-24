#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int num)
{
	write(1, "I wont't die!!\n", 15);
}

void k()
{
	sleep(3);
	write(1, "here", 4);
	exit(0);
}

int main()
{

	signal(SIGINT, handler);
	signal(SIGKILL, k);
	while (1)
	{
		printf("your server id is: %d\n", getpid());
		sleep(1);
	}
}
#include <stdlib.h>
#include <stdio.h>


void send_signal(int pid, char c){
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if(c & 128 ) {
			kill(pid, SIGUSR1);
			} else {
			kill(pid, SIGUSR2);
			}
		c = c << 1;
		printf("iteration %d\n", bit);
		bit++;
		usleep(900);
	}
}

int main(int argc, char **argv){


	int pid;
	int i;
	char *bit;

	if(argc != 3){
		printf("Please input the PID and the string to send");
		return (0);
	}

	pid = atoi(argv[1]);
	printf("%d\n", pid + 1);
	i =0;
	while(argv[2][i]){
		send_signal(pid, argv[2][i]);
		printf("%c", argv[2][i]);
		i++;
	}
}
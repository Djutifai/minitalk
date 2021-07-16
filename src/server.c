#include "../includes/minitalk.h"
#include <stdio.h>

void	ft_sighandler(int signum)
{
	if (signum == SIGUSR1)
	{

	}
}

int		main(void)
{
	pid_t	server_pid;
	int		sleeptime;

	sleeptime = 1;
	server_pid = getpid();
	write(1, "Server PID is: ", 15);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_sighandler);
	while(sleeptime > 0)
	{
		sleeptime = sleep(600);
	}
}

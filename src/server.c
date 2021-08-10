#include "../includes/minitalk.h"

void	ft_sighandler(int signum)
{
	static int	num;
	static int	counter;
	char		c;

	if (!num)
		num = 0;
	if (!counter)
		counter = 1;
	if (signum == SIGUSR1)
		num |= 1;
	if (counter == 7)
	{
		c = num;
		write(1, &c, 1);
		num = 0;
		counter = 1;
	}
	else
	{
		counter++;
		num <<= 1;
	}
}

int	main(void)
{
	pid_t	server_pid;
	int		sleeptime;

	sleeptime = 1;
	server_pid = getpid();
	write(1, "Server PID is: ", 15);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_sighandler);
	signal(SIGUSR2, ft_sighandler);
	while (sleeptime > 0)
	{
		sleeptime = sleep(120);
	}
	write(1, "\nTime ran out\n", 14);
}

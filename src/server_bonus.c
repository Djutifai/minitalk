#include "../includes/minitalk_bonus.h"

void	ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int	counter;
	static char	c;

	(void)context;
	(void)siginfo;
	if (!counter)
		counter = 1 << 7;
	if (!c)
		c = 0;
	if (signum == SIGUSR1)
		c |= counter;
	counter >>= 1;
	if (counter == 0)
	{
		write(1, &c, 1);
		c = 0;
		counter = 1 << 7;
	}
}

int	main(void)
{
	int					sleeptime;
	struct sigaction	act;

	act.sa_sigaction = ft_sighandler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	if ((sigaction(SIGUSR1, &act, 0)) == -1)
		write(1, "Error! Check what you are doing\n", 32);
	if ((sigaction(SIGUSR2, &act, 0)) == -1)
		write(1, "Error! Check what you are doing\n", 32);
	sleeptime = 1;
	write(1, "Server PID is: ", 15);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (sleeptime > 0)
	{
		sleeptime = sleep(120);
	}
	write(1, "\nTime ran out\n", 14);
}

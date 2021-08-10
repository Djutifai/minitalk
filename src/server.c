#include "../includes/minitalk.h"

void	ft_sighandler(int signum, siginfo_t *sig, void *context)
{
	static int	counter;
	static char		c;

	(void)context;
	if (!c)
		c = 0;
	if (!counter)
		counter = 1;
	if (signum == SIGUSR1)
		c |= 1;
	if (counter == 7)
	{
		write(1, &c, 1);
		c = 0;
		counter = 0;
	}
	counter++;
	c <<= 1;
	kill(sig->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t	server_pid;
	int		sleeptime;
	struct	sigaction sigac;
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = ft_sighandler;
	sigaction(SIGUSR1, &sigac, NULL);
	sigaction(SIGUSR2, &sigac, NULL);

	sleeptime = 1;
	server_pid = getpid();
	write(1, "Server PID is: ", 15);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	while (sleeptime > 0)
	{
		sleeptime = sleep(120);
	}
	write(1, "\nTime ran out\n", 14);
}

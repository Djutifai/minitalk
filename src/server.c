#include "../includes/minitalk.h"

static void	ft_shift_bit(int signum, pid_t client_pid)
{
	static int	counter;
	static char	c;

	if (!counter)
		counter = 1 << 7;
	if (!c)
		c = 0;
	if (signum == SIGUSR1)
		c |= counter;
	counter >>= 1;
	if (counter == 0)
	{
		if (c == 0)
			return ;
		write(1, &c, 1);
		c = 0;
		counter = 1 << 7;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		write (1, "Error in sending signals!\n", 26);
}

static void ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int nullCounter;

	(void)context;
	if (!nullCounter)
		nullCounter = 0;
	if (signum == SIGUSR1)
		nullCounter = 0;
	else
		nullCounter++;
	if (nullCounter == 8)
	{
		write(1, "\nThe \"minitalk\" is done :D", 26);
		return ;
	}
	ft_shift_bit(signum, siginfo->si_pid);
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
	if (sleep(15) == 0)
		write(1, "\nTime ran out\n", 14);
	while (sleeptime > 0)	
		sleeptime = sleep(6);
	write(1, "\nThanks for using my program!", 30);
}

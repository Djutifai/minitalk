#include "../includes/minitalk.h"
#include <stdio.h>
static void	ft_shift_bit(int signum, pid_t client_pid, int len)
{
	static int	counter;
	static int	index;
	static char *str;

	if (!counter)
		counter = 1 << 7;
	if (!index)
	{
		index = 0;
		str = (char *)malloc(sizeof(*str) * len + 1);
		printf("HELLO LEN IS %d\n", len);
		if (!str)
			if (kill(client_pid, SIGUSR2) == -1)
				write(1, "Error in sending signals\n", 26);
	}
	if (signum == SIGUSR1)
		str[index] |= counter;
	counter >>= 1;
	if (counter == 0)
	{
		if (str[index] == 0)
			return ;
		if (index == len)
			write(1, str, len);
		index++;
		counter = 1 << 7;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		write (1, "Error in sending signals!\n", 26);
}

static void ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int nullCounter;
	static int firstLaunch;
	static int len;

	(void)context;
	if (!nullCounter)
		nullCounter = 0;
	if (!firstLaunch || firstLaunch < 8)
	{
		firstLaunch++;
		ft_get_len(signum, siginfo->si_pid, &len);
		return ;
	}
	if (signum == SIGUSR1)
		nullCounter = 0;
	else
		nullCounter++;
	if (nullCounter == 16)
	{
		write(1, "\nThe \"minitalk\" is done :D", 26);
		return ;
	}
	ft_shift_bit(signum, siginfo->si_pid, len);
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
	if (sleep(60) == 0)
		write(1, "\nTime ran out\n", 14);
	while (sleeptime > 0)	
		sleeptime = sleep(1);
	write(1, "\nThanks for using my program!\n", 31);
}

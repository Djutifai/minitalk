#include "../includes/minitalk.h"

static void	ft_shift_bit(int signum, pid_t client_pid, int len)
{
	static char *str;
	static int	counter;
	static int	index;

	if (!str)
	{
		index = 0;
		str = (char *)malloc(sizeof(*str) * len);
		if (!str)
		{
			ft_send_signal(client_pid, SIGUSR2);
			return ;
		}
		counter = 1 << 7;
	}
	if (signum == SIGUSR1)
		str[index] |= counter;
	counter >>= 1;
	if (!counter)
	{
		index++;
		counter = 1 << 7;
	}
	if (index == len)
	{
		ft_write_str(str);
		printf("\n index - %d len - %d", index, len);
		return ;
	}
	ft_send_signal(client_pid, SIGUSR1);
}

static void ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int	isRecievingLen;
	static int	len;

	(void)context;
	if (!len)
		len = 0;
	if (!isRecievingLen || isRecievingLen < 30)
	{
		isRecievingLen++;
		ft_get_len(signum, siginfo->si_pid, &len);
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

#include "minitalk.h"

static void	ft_shift_bit(int signum, pid_t client_pid, int len)
{
	static char	*str;
	static int	counter;
	static int	index;

	if (!str)
	{
		if (ft_if_not_str(&index, &str, client_pid, len) == -1)
			return ;
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
		ft_write_and_free(&str);
		return ;
	}
	ft_send_signal(client_pid, SIGUSR1);
}

static void	ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int		is_recieving_len;
	static int		len;
	static pid_t	my_pid;

	if (!my_pid || my_pid != siginfo->si_pid)
	{
		my_pid = siginfo->si_pid;
		len = 0;
		is_recieving_len = 0;
	}
	(void)context;
	if (!is_recieving_len || is_recieving_len < 31)
	{
		is_recieving_len++;
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
		sleeptime = sleep(15);
	write(1, "\nThanks for using my program!\n", 31);
}

#include "../includes/minitalk.h"

static void	ft_send_char(char c, int counter, pid_t serv_pid)
{
	if (c & counter)
		ft_send_signal(serv_pid, SIGUSR1);
	else
		ft_send_signal(serv_pid, SIGUSR2);
}

static void	ft_send_str(pid_t server_pid, char *str)
{
	static char		*myStr;
	static pid_t	myPid;
	static int		counter;

	if (!myPid)
	{
		myStr = str;
		myPid = server_pid;
		counter = 1 << 7;
		return ;
	}
	if (!*myStr)
		return ;
	ft_send_char(*myStr, counter, myPid);
	counter >>= 1;
	if (!counter)
	{
		write(1, myStr, 1);
		counter = 1 << 7;
		myStr++;
	}
	usleep(30);
}

static void	ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int	isSendingLen;

	if (signum == SIGUSR2)
	{
		ft_write_str("Error on server side!\n");
		exit(-1);
	}
	if (!isSendingLen || isSendingLen < 30)
	{
		isSendingLen++;
		ft_send_len(0, 0);
		return ;
	}
	(void)siginfo;
	(void)context;
	ft_send_str(0, 0);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	act;
	int					sleeptime;

	if (ft_check_everything(argc, argv[1]) == -1)
		return (-1);
	act.sa_sigaction = ft_sighandler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if ((sigaction(SIGUSR1, &act, 0)) == -1)
		ft_write_str("Error! Check what you are doing\n");
	if ((sigaction(SIGUSR2, &act, 0)) == -1)
		ft_write_str("Error! Check what you are doing\n");
	sleeptime = 1;
	server_pid = (pid_t)ft_atoi(argv[1]);
	ft_send_str(server_pid, argv[2]);
	ft_send_len(server_pid, ft_strlen(argv[2]));
	while (sleeptime > 0)
		sleeptime = sleep(2);
	ft_write_str("Thanks for using my program!\n");
	return (0);
}

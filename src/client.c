#include "../includes/minitalk.h"

static void ft_send_char(char c, int counter, pid_t serv_pid)
{
	if (c & counter)
	{
		if (kill(serv_pid, SIGUSR1) == -1)
			write(1, "Error in sending signals!\n", 26);
	}
	else
	{
		if (kill(serv_pid, SIGUSR2) == -1)
			write(1, "Error in sending signals!\n", 26);
	}
}

static void ft_eof(pid_t server_pid)
{
	static int	counter;

	if (!counter)
		counter = 0;
	if (counter == 16)
		return ;
	if (kill(server_pid, SIGUSR2) == -1)
		write(1, "Error in sending signals!\n", 26);
	counter++;
}

static void	ft_send_str(pid_t server_pid, char *str)
{
	static int		counter;
	static char		*myStr;
	static pid_t	serv_pid;

	if (!serv_pid)
	{
		myStr = str;
		serv_pid = server_pid;
		counter = 1 << 7;
		return ;
	}
	if (!myStr)
	{
		ft_eof(server_pid);
		return ;
	}
	if (!counter)
	{
		counter = 1 << 7;
		myStr++;
	}
	ft_send_char(*myStr, counter, serv_pid);
	counter >>= 1;
	usleep(15);
}

static void ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int firstLaunch;

	if (signum == SIGUSR2)
	{
		write(1, "Error on server side!\n", 22);
	}
	if (!firstLaunch || firstLaunch < 8)
	{
		firstLaunch++;
		ft_send_len(0, 0);
	}
	(void)signum;
	(void)siginfo;
	(void)context;
	ft_send_str(0, 0);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	size_t				i;
	struct sigaction	act;
	int					sleeptime;

	if (ft_check_everything(argc, argv[1]) == -1)
		return (-1);
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
	i = 0;	
	server_pid = (pid_t)ft_atoi(argv[1]);
	ft_send_str(server_pid, argv[2]);
	ft_send_len(server_pid, ft_strlen(argv[2]));
	while (sleeptime > 0)
		sleeptime = sleep(6);
	write(1, "\nThanks for using my program!", 30);
}

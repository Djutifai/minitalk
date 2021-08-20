#include "../includes/minitalk.h"

void	ft_send_str(pid_t server_pid, char *str)
{
	int	counter;
	static char *myStr;
	static pid serv_pid;

	if (!serv_pid)
	{
		myStr = str;
		serv_pid = server_pid;
	}
	counter = 1 << 7;
	while (counter)
	{
		if (c & counter)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				write(1, "Error in sending signals!\n", 26);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				write(1, "Error in sending signals!\n", 26);
		}
		counter >>= 1;
		usleep(100);
	}
}

static int ft_check_everything(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "Check arguments!\nRight usage ./client pid message\n", 50);
		return (-1);
	}
	if (ft_validatestr(argv[1]) == -1)
	{
		write(1, "Invalid PID\n", 12);
		return (-1);
	}
	return (1);
}

static void ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int nullCounter;

	nullCounter = 0;
	(void)context;
	if (signum == SIGUSR1)
		nullCounter = 0;
	else
		nullCounter++;
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	size_t				i;
	struct sigaction	act;

	if (ft_check_everything(argc, argv) == -1)
			return (-1);
	act.sa_sigaction = ft_sighandler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	i = 0;	
	server_pid = (pid_t)ft_atoi(argv[1]);
	ft_send_str(server_pid, argv[2]);
	while (1)
	{
		ft_send_str(server_pid, 0);
	}
}

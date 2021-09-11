#include "minitalk.h"

static void	ft_send_char(char c, int counter, pid_t serv_pid)
{
	if (c & counter)
		ft_send_signal(serv_pid, SIGUSR1);
	else
		ft_send_signal(serv_pid, SIGUSR2);
}

static void	ft_send_str(pid_t server_pid, char *str)
{
	static char		*my_str;
	static pid_t	my_pid;
	static int		counter;

	if (!my_pid)
	{
		my_str = str;
		my_pid = server_pid;
		counter = 1 << 7;
		return ;
	}
	if (!*my_str)
		return ;
	usleep(20);
	ft_send_char(*my_str, counter, my_pid);
	counter >>= 1;
	if (!counter)
	{
		counter = 1 << 7;
		my_str++;
	}	
}

static void	ft_sighandler(int signum, siginfo_t *siginfo, void *context)
{
	static int	is_sending_len;

	if (signum == SIGUSR2)
	{
		ft_write_str("Error on server side!\n");
		exit(-1);
	}
	if (!is_sending_len || is_sending_len < 30)
	{
		is_sending_len++;
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

	if (ft_check_everything(argc, argv) == -1)
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
		sleeptime = sleep(1);
	ft_write_str("Thanks for using my program!\n");
	return (0);
}

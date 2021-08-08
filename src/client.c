#include "../includes/minitalk.h"

static void ft_exit(pid_t server_pid)
{
	size_t i;

	i = 7;
	while (i)
	{
		kill(server_pid, SIGUSR2);
		i--;
	}
	exit(0);
}

static void	ft_send_char(pid_t server_pid, char *str)
{
	static int		counter;
	static size_t	i;
	static char		*mystr;
	static pid_t	pid;

	if (!pid)
	{
		mystr = str;
		pid = server_pid;
	}
	if (!counter)
	{
		counter = 64;
		if (!i)
			i = 0;
		else
			i++;
		if (!mystr[i])
			ft_exit(pid);
	}
	if (mystr[i] & counter)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	counter /= 2;
}

static void ft_sighandler(int sig)
{
	(void)sig;
	ft_send_char(0, 0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	size_t	i;

	i = 0;
	if (argc != 3)
	{
		write(1, "Check arguments!\nRight usage ./client pid message\n", 50);
		return (0);
	}
	server_pid = (pid_t)ft_atoi(argv[1]);
	signal(SIGUSR1, ft_sighandler);
	signal(SIGUSR2, ft_sighandler);
	ft_send_char(server_pid, argv[2]);
	while (1)
	{
		pause();
	}
	return (0);
}

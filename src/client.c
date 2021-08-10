#include "../includes/minitalk.h"

static void	ft_send_char(pid_t server_pid, char *str)
{
	static int		counter;
	static size_t	i;
	static char		*mystr;
	static pid_t	pid;

	if (!counter)
	{
		counter = 1 << 6;
		if (!i)
			i = 0;
		else
		{
			write(1, " ", 1);
			write(1, &mystr[i], 1);
			write(1, "\n", 1);
			i++;
		}
		if (!mystr)
		{
			mystr = str;
			pid = server_pid;
		}
		if (!mystr[i])
			exit(1);
	}
	if (mystr[i] & counter)
	{
		write(1, "1", 1);
		kill(pid, SIGUSR1);
	}
	else
	{
		write(1, "0", 1);
		kill(pid, SIGUSR2);
	}
	counter >>= 1;
}

static void ft_sighandler(int sig)
{
	(void) sig;
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
}

#include "../includes/minitalk_bonus.h"

void	ft_send_char(pid_t server_pid, char c)
{
	int	counter;

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
	while (argv[2][i])
	{
		ft_send_char(server_pid, argv[2][i]);
		i++;
	}
}

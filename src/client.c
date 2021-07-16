#include <stdio.h>
#include "../includes/minitalk.h"

int main(int argc, char **argv)
{
	pid_t server_pid;
	(void)argc;

	server_pid = (pid_t)ft_atoi(argv[1]);
	kill(server_pid, SIGKILL);
}

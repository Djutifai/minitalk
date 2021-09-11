#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_validate_pid(const char *str);
int		ft_check_everything(int argc, char **argv);
int		ft_atoi(char const *str);
void	ft_putnbr(int nb);
void	ft_get_len(int signum, pid_t server_pid, int *len);
int		ft_strlen(const char *str);
void	ft_send_len(pid_t server_pid, int len);
void	ft_send_signal(pid_t pid, int signum);
void	ft_write_str(char *str);
int		ft_if_not_str(int *index, char **str, pid_t client_pid, \
			int len);
void	ft_write_and_free(char **str);
void	*ft_calloc(int len, int size);

#endif

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int	main(int ac, char **av);
int	*convert_into_int(int ac, char **av);
int	ft_atoi(const char *str);
int	is_args_valid(int **tab);

#endif
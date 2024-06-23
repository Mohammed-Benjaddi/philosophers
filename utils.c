#include "philo.h"

void ft_error()
{
  printf("Error: invalid arguments\n");
  exit(1);
}

int init_vars(char **args, data_t *data)
{
  data->n_philos = ft_atoi(args[0]);
  data->philos.time_to_die = ft_atoi(args[1]);
  data->philos.time_to_eat = ft_atoi(args[2]);
  data->philos.time_to_sleep = ft_atoi(args[3]);
  if(args[4])
  {
    data->philos.times_to_eat = ft_atoi(args[4]);
    if(data->philos.times_to_eat <= 0)
      return 0;
  }
  if(data->philos.time_to_die <= 0 || data->philos.time_to_eat <= 0
    || data->philos.time_to_sleep <= 0)
  return 0;
  return 1;
} 

int ft_atoi(char *str)
{
  int result;
  int sign;
  int i;

  result = 0;
  sign = 1;
  i = 0;
  if(!str)
    return 0;  
  while((str[i] >= 9 && str[i]<= 13) || str[i] == 32)
    i++;
  if(str[i] == '+' || str[i] == '-')
  {
    if(str[i] == '-')
      sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9')
  {
    result = (result * 10) + (str[i] - '0');
    i++;
  }
  return (result * sign);
}

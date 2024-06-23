#include "philo.h"

void ft_error(char *msg)
{
  printf("Error: %s\n", msg);
}

int init_vars(char **args, data_t *data)
{
  data->n_philos = ft_atoi(args[0]);
  data->time_to_die = ft_atoi(args[1]);
  data->time_to_eat = ft_atoi(args[2]);
  data->time_to_sleep = ft_atoi(args[3]);
  if(args[4])
  {
    data->times_to_eat = ft_atoi(args[4]);
    if(data->times_to_eat <= 0)
      return 0;
  }
  if(data->time_to_die <= 0 || data->time_to_eat <= 0
    || data->time_to_sleep <= 0 || data->n_philos <= 0
    || data->n_philos > 200)
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

int init_mutex(data_t *data)
{
  int i;

  i = 0;
  while (i < data->n_philos)
  {
    if(pthread_mutex_init(&data->forks[i], NULL) != 0)
      return 0;
    i++;
  }
  return 1;
}

void *philo_routine(void *data)
{
  printf("------> philo routine has been excuted\n");

  return NULL;
}

int init_philos(data_t *data)
{
  int i;

  i = 0;
  while (i < data->n_philos)
  {
    data->philos[i].id = i;
    data->philos[i].left_fork = i;
    data->philos[i].right_fork = (i + 1) % data->n_philos;
    if(pthread_create(&data->philos[i].thread, NULL, philo_routine, NULL) != 0)
      return 0;
    if(pthread_join(data->philos[i].thread, NULL))
      return 0;
    i++;  
  }
  return 1;
}
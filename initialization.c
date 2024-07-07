#include "philo.h"

int init_program(char **args, data_t *data)
{
  data->n_philos = ft_atoi(args[0]);
  data->philos = (philo_t *)malloc(sizeof(philo_t) * data->n_philos);
  data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philos);
  data->is_dead = 0;
  // data->someone_died = 0;
  data->start_time = get_current_time();
  // printf("-----> %lu\n", data->start_time);
  data->time_to_die = ft_atoi(args[1]);
  data->time_to_eat = ft_atoi(args[2]);
  data->time_to_sleep = ft_atoi(args[3]);
  if (args[4])
    data->times_to_eat = ft_atoi(args[4]);
  else
    data->times_to_eat = -1;  
  if(data->time_to_die <= 0 || data->time_to_eat <= 0
    || data->time_to_sleep <= 0 || data->n_philos <= 0
    || data->n_philos > 200 || (args[4] && ft_atoi(args[4]) <= 0))
    return (0);
  if(!init_mutex(data))
    return 0;
  init_philos(data);
  return 1;
}

int init_mutex(data_t *data)
{
  int i;

  i = 0;
  while (i < data->n_philos)
  {
    if(pthread_mutex_init(&data->forks[i], NULL) != 0)
      return (ft_error("mutex init failed"), 0);
    if(pthread_mutex_init(&data->philos[i].check_meal, NULL) != 0)
      return (ft_error("mutex init failed"), 0);
    // if(pthread_mutex_init(&data->philos[i].is_eating, NULL) != 0)
    //   return (ft_error("mutex init failed"), 0);
    i++;
  }
  if(pthread_mutex_init(&data->print, NULL) != 0)
    return (ft_error("mutex init failed"), 0);
  if(pthread_mutex_init(&data->dead_mutex, NULL) != 0)
    return (ft_error("mutex init failed"), 0);
  // if(pthread_mutex_init(&data->someone_died_m, NULL) != 0)
  //   return (ft_error("mutex init failed"), 0);
  // if(pthread_mutex_init(&data->is_dead_m, NULL) != 0)
  //   return (ft_error("mutex init failed"), 0);
  return 1;
}

void init_philos(data_t *data)
{
  int i;

  i = 0;
  while (i < data->n_philos)
  {
    data->philos[i].data = data;
    data->philos[i].id = i + 1;
    data->philos[i].eat_count = 0;
    data->philos[i].left_fork = i;
    data->philos[i].right_fork = (i + 1) % data->n_philos;
    data->philos[i].last_meal = get_current_time();
    i++;
  }
}

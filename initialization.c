#include "philo.h"

int init_vars(char **args, data_t *data)
{
  data->n_philos = ft_atoi(args[0]);
  data->philos = (philo_t *)malloc(sizeof(philo_t) * data->n_philos);
  data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philos);
  data->is_dead = 0;
  data->someone_died = 0;
  if(!init_mutex(data))
    return (ft_error("Something went wrong"), 0);
  if(!init_philos(data, args))
    return (0);
  return 1;
}

int init_mutex(data_t *data)
{
  int i;

  i = 0;

  while (i < data->n_philos)
  {
    if(pthread_mutex_init(&data->forks[i], NULL) != 0)
      return 0;
    if(pthread_mutex_init(&data->philos[i].check_meal, NULL) != 0)
      return 0;
    if(pthread_mutex_init(&data->philos[i].is_eating, NULL) != 0)
      return 0;
    i++;
  }
  if(pthread_mutex_init(&data->print, NULL) != 0)
    return 0;
  if(pthread_mutex_init(&data->dead_mutex, NULL) != 0)
    return 0;
  if(pthread_mutex_init(&data->someone_died_m, NULL) != 0)
    return 0;
  return 1;
}

int init_philos_vars(philo_t *philo, int i, int n_philos, char **args)
{
  philo->id = i + 1;
  philo->eat_count = 0;
  philo->left_fork = i;
  philo->right_fork = (i + 1) % n_philos;
  philo->current_time = get_current_time();
  philo->time_to_die = ft_atoi(args[1]);
  philo->time_to_eat = ft_atoi(args[2]);
  philo->time_to_sleep = ft_atoi(args[3]);
  if (i % 2 == 0)
    philo->deadlock = 0;
  else
    philo->deadlock = 1;
  if (args[4])
    philo->times_to_eat = ft_atoi(args[4]);
  else
    philo->times_to_eat = 2147483647;
  if(philo->time_to_die <= 0 || philo->time_to_eat <= 0
    || philo->time_to_sleep <= 0 || n_philos <= 0
    || n_philos > 200 || philo->times_to_eat <= 0)
    return 0;
  printf("times to eat: %d\n", philo->times_to_eat);
  return 1;
}

int init_philos(data_t *data, char **av)
{
  int i;

  i = 0;
  while (i < data->n_philos)
  {
    if(!init_philos_vars(&data->philos[i], i, data->n_philos, av))
      return 0;
    data->philos[i].data = data;
    pthread_mutex_lock(&data->philos[i].check_meal);
    data->philos[i].last_meal = get_current_time();
    pthread_mutex_unlock(&data->philos[i].check_meal);
    if(pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
      return 0;
    i++;
  } 
  while (1)
  {
    // if(data->is_dead)
    //   return 0;
    if(!data->is_dead)
    {
      if(check_dead_philo(data) == -1)
      {
        printf("at infinite loop\n");
        return 0;
      }
      usleep(50);
    }
    else
    {
      printf("one of the philosophers was died\n");
      // exit(1);
      return 0;
    }
  }
  i = 0;
  while(i < data->n_philos)
    pthread_join(data->philos[i++].thread, NULL);
  return 1;
}

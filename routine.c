#include "philo.h"

void ft_think(philo_t *philo)
{
  print_msg(philo, 3);
}

void ft_sleep(philo_t *philo)
{
  print_msg(philo, 2);
  ft_wait(philo->data->time_to_sleep);
}

void check_dead_philo(data_t *data)
{
  int i;

  i = 0;
  philo_t *philos;
  philos = data->philos;
  while (i < data->n_philos)
  {
    // printf("current time: %zu\n", get_current_time());
    // pthread_mutex_lock(&philos[i].check_meal);
    if(get_current_time() - philos[i].last_meal >= philos[i].data->times_to_eat)
    {
      // pthread_mutex_lock(&philos[i].data->is_dead_m);
      data->is_dead = 1;
      // pthread_mutex_unlock(&philos[i].data->is_dead_m);
      print_msg(&philos[i], -1);
      break;
    }
    // pthread_mutex_unlock(&philos[i].check_meal);
    i++;
    usleep(100);
  }
  // i = 0;

  // while (i < data->n_philos && philos[i].eat_count >= philos[i].times_to_eat)
  //   i++;

  // if(i == data->n_philos)
  // {
  //   print_msg(&philos[0], 25);
  //   return 1;
  // }
}

void ft_eat(philo_t *philo)
{
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  print_msg(philo, 4);
  print_msg(philo, 5);
  print_msg(philo, 1);

  pthread_mutex_lock(&philo->check_meal);
  philo->last_meal = get_current_time();
  // printf("-------> start: %zu\n", philo->data->start_time);
  pthread_mutex_unlock(&philo->check_meal);

  ft_wait(philo->data->time_to_eat);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);

  // pthread_mutex_lock(&philo->data->is_eating);
  philo->eat_count++;
  // pthread_mutex_unlock(&philo->data->isj_eating);
}

void destroy_all_forks(data_t *data, int size)
{
  int i;
  pthread_mutex_t *forks;
  philo_t *philos;

  i = 0;
  forks = data->forks;
  philos = data->philos;
  while(i < data->n_philos)
    pthread_join(data->philos[i++].thread, NULL);
  i = 0;
  while (i < size)
  {
    pthread_mutex_destroy(&forks[i]);
    // pthread_mutex_destroy(&philos[i].is_eating);
    pthread_mutex_destroy(&philos[i].check_meal);
    i++;
  }
  free(forks);
  free(philos);
  // printf("all forks have been destroyed successfully\n");
}

void *philo_routine(void *philos)
{
  philo_t *philo;

  philo = (philo_t *)philos;
  philo = (philo_t *) philos;
  if(philo->id % 2 == 0)
    ft_wait(5500);
  while (!philo->data->is_dead)
  {
    ft_eat(philo);
    ft_sleep(philo);
    ft_think(philo);
  }
  return NULL;
}

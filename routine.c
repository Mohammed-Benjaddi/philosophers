#include "philo.h"

void ft_think(philo_t *philo)
{
  print_msg(philo, 3);
}

void ft_sleep(philo_t *philo)
{
  print_msg(philo, 2);
  ft_wait(philo->time_to_sleep);
}

void finish_eating(philo_t *philo, int right_fork)
{
  philo->deadlock = 1;
  philo->data->philos[right_fork].deadlock = 0;
}

void ft_eat(philo_t *philo)
{
  pthread_mutex_lock(&philo->data->print);
  philo->meal_time = get_current_time();
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  print_msg(philo, 4);
  pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  print_msg(philo, 5);
  print_msg(philo, 1);
  ft_wait(philo->time_to_eat);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
  pthread_mutex_unlock(&philo->data->print);
  finish_eating(philo, philo->right_fork);
  // if(get_current_time() - philo->meal_time >= philo->time_to_die)
  // printf("%sphilo is dead%s\n", RED, NC);
}

void destroy_all_forks(pthread_mutex_t *forks, int size)
{
  int i;

  i = 0;
  while (i < size)
  {
    pthread_mutex_destroy(&forks[i]);
    i++;
  }
  printf("all forks have been destroyed successfully\n");
}

void *philo_routine(void *philos)
{
  philo_t philo;

  philo = *(philo_t *) philos;
  if(philo.id % 2 == 0)
    ft_wait(philo.time_to_eat);
  while (1)
  {
    ft_eat(&philo);
    ft_sleep(&philo);
    ft_think(&philo);
  }
  return NULL;
}

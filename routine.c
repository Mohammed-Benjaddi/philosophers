#include "philo.h"

void ft_think(philo_t *philo)
{
  printf("%s%d %d is thinking%s\n", MAGENTA, get_current_time() - philo->current_time, philo->id, NC);
}

void ft_sleep(philo_t *philo)
{
  printf("%s%d %d is sleeping%s\n", CYAN, get_current_time() - philo->current_time, philo->id, NC);
  ft_wait(philo->time_to_sleep);
}

void finish_eating(philo_t *philo, int right_fork)
{
  philo->deadlock = 1;
  philo->data->philos[right_fork].deadlock = 0;
}

void ft_eat(philo_t *philo)
{
  philo->meal_time = get_current_time();
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  printf("%s%d %d has taken the left fork%s\n", YELLOW, get_current_time() - philo->current_time, philo->id, NC);
  pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  printf("%s%d %d has taken the right fork%s\n", YELLOW, get_current_time() - philo->current_time, philo->id, NC);
  printf("%s%d %d is eating%s\n", GREEN, get_current_time() - philo->current_time, philo->id, NC);
  ft_wait(philo->time_to_eat);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
  finish_eating(philo, philo->right_fork);
  if(get_current_time() - philo->meal_time >= philo->time_to_die)
    printf("%sphilo is dead%s\n", RED, NC);
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
  {
    printf("%d is waiting...\n", philo.id);
    ft_wait(200);
  }
  while (1)
  {
    ft_eat(&philo);
    ft_sleep(&philo);
    ft_think(&philo);
  }
  return NULL;
}

#include "philo.h"

void *only_one_philo(void *philo_data)
{
  philo_t *philo;

  philo = (philo_t *) philo_data;  
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  // ft_wait(philo->data->time_to_die + 100);
  philo->data->is_dead = 1;
  // pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  print_msg(philo, 4);
  pthread_mutex_lock(&philo->check_meal);
  philo->last_meal = get_current_time();
  pthread_mutex_unlock(&philo->check_meal);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  // pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
  return NULL;
}

void start_program(data_t *data)
{
  int i;

  i = -1;
  if(data->n_philos == 1)
    pthread_create(&data->philos[0].thread, NULL, only_one_philo, &data->philos[0]);
  else
  {
    while(++i < data->n_philos)
      pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
    while(!data->is_dead)
      check_dead_philo(data);
  }
}

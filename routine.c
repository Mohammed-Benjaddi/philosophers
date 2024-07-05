#include "philo.h"

void ft_think(philo_t *philo)
{
  // pthread_mutex_lock(&philo->data->print);
  print_msg(philo, 3);
  // pthread_mutex_unlock(&philo->data->print);
}

void ft_sleep(philo_t *philo)
{
  // pthread_mutex_lock(&philo->data->print);
  print_msg(philo, 2);
  ft_wait(philo->time_to_sleep);
  // pthread_mutex_unlock(&philo->data->print);
}

// void finish_eating(philo_t *philo, int right_fork)
// {
//   philo->deadlock = 1;
//   philo->data->philos[right_fork].deadlock = 0;
// }

int check_dead_philo(data_t *data)
{
  int i;

  i = 0;
  philo_t *philos;
  philos = data->philos;
  while (i < data->n_philos)
  {
    pthread_mutex_lock(&philos[i].check_meal);
    int curr = get_current_time();
    if(curr - philos[i].last_meal >= philos[i].time_to_die)
    {
      pthread_mutex_lock(&philos[i].data->is_dead_m);
      data->is_dead = 1;
      pthread_mutex_unlock(&philos[i].data->is_dead_m);
      print_msg(&philos[i], -1);
        return 1;
    }
    pthread_mutex_unlock(&philos[i].check_meal);
    i++;
    usleep(70);
  }
  // i = 0;

  // while (i < data->n_philos && philos[i].eat_count >= philos[i].times_to_eat)
  //   i++;

  // if(i == data->n_philos)
  // {
  //   print_msg(&philos[0], 25);
  //   return 1;
  // }
  return 0;
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
  pthread_mutex_unlock(&philo->check_meal);

  ft_wait(philo->time_to_eat);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);

  pthread_mutex_lock(&philo->is_eating);
  philo->eat_count++;
  pthread_mutex_unlock(&philo->is_eating);
}

void destroy_all_forks(data_t *data, int size)
{
  int i;
  pthread_mutex_t *forks;
  philo_t *philos;

  i = 0;
  forks = data->forks;
  philos = data->philos;
  while (i < size)
  {
    pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(&philos[i].is_eating);
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

  philo = (philo_t *) philos;
  if(philo->id % 2 == 0)
    usleep(1500);
    //ft_wait(philo->time_to_eat);
  while (1)
  {
    pthread_mutex_lock(&philo->data->is_dead_m);
    if(philo->data->is_dead)
    {
      break;
      pthread_mutex_unlock(&philo->data->is_dead_m);
    }
    pthread_mutex_unlock(&philo->data->is_dead_m);
    if(check_dead_philo(philo->data))
      break;
    ft_eat(philo);
    ft_sleep(philo);
    ft_think(philo);
  }
  return NULL;
}

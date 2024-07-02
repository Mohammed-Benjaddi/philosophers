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
    // usleep(100);
    pthread_mutex_lock(&philos[i].check_meal);
    // printf("at checking the dead =====> %d\n", data->philos[i].last_meal);
    int curr = get_current_time();
    // pthread_mutex_lock(&philos[i].check_meal);
    if(curr - philos[i].last_meal >= philos[i].time_to_die)
    {
      // pthread_mutex_lock(&data->dead_mutex);
      data->is_dead = 1;
      // pthread_mutex_unlock(&data->dead_mutex);
      if(print_msg(&philos[i], -1) == -1)
      {
        printf("------------> returned -1\n");
        return -1;
      }
    }
    pthread_mutex_unlock(&philos[i].check_meal);
    i++;
    usleep(70);
  }
  return 1;
}

void ft_eat(philo_t *philo)
{
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  print_msg(philo, 4);
  print_msg(philo, 5);
  print_msg(philo, 1);
  ft_wait(philo->time_to_eat);
  // pthread_mutex_lock(&philo->check_meal);
  // philo->last_meal = get_current_time();
  // pthread_mutex_unlock(&philo->check_meal);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
  // finish_eating(philo, philo->right_fork);
  pthread_mutex_lock(&philo->check_meal);
  philo->last_meal = get_current_time();
  pthread_mutex_unlock(&philo->check_meal);
  // printf("at eating %d ========> %p\n", philo->id, &philo);
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

  // printf("all forks have been destroyed successfully\n");
}

void *philo_routine(void *philos)
{
  philo_t *philo;

  philo = (philo_t *) philos;
  if(philo->id % 2 == 0)
    ft_wait(philo->time_to_eat);
  while (1)
  {
    // pthread_mutex_lock(&philo->data->dead_mutex);
    // if(!philo->data->is_dead)
    // {
      ft_eat(philo);
      ft_sleep(philo);
      ft_think(philo);
      // check_is_dead(philo.data);
      if(!check_dead_philo(philo->data))
        break;
    // }
    // pthread_mutex_unlock(&philo->data->dead_mutex);
  }
  return NULL;
}

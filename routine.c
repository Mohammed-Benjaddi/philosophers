#include "philo.h"

void ft_think(philo_t *philo)
{
  print_msg(philo, MAGENTA, "is thinking");
}

void ft_sleep(philo_t *philo)
{
  print_msg(philo, CYAN, "is sleeping");
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
    pthread_mutex_lock(&philos[i].check_meal);
    if(get_current_time() - philos[i].last_meal >= philos[i].data->time_to_die)
    {
      pthread_mutex_unlock(&philos[i].check_meal);
      pthread_mutex_lock(&philos[i].data->dead_mutex);
      data->is_dead = 1;
      pthread_mutex_unlock(&philos[i].data->dead_mutex);
      pthread_mutex_lock(&philos[i].data->print);
      // print_msg(&philos[i], RED, "is died");
      printf("%s%lld %d is died%s\n", RED, get_current_time() - philos[i].data->start_time, philos[i].id, NC);
      pthread_mutex_unlock(&philos[i].data->print);
      // data->finished = 1;

      break;
    }
    pthread_mutex_unlock(&philos[i].check_meal);
    i++;
    // usleep(100);
  }
  i = 0;
  int counter = 0;
  if(data->times_to_eat != -1)
  {
    // while (i < data->n_philos && philos[i].eat_count >= data->times_to_eat)
    while (i < data->n_philos)
    {
      pthread_mutex_lock(&philos[i].is_eating);
      if(philos[i].eat_count >= data->times_to_eat)
        counter++;
      pthread_mutex_unlock(&philos[i].is_eating);
      i++;
      usleep(100);
    }
    if(i == data->n_philos)
    {
      // print_msg(&philos[0], 25);
      data->all_philos_ate = 1;
    }
  }
  
}

void ft_eat(philo_t *philo)
{
  pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
  print_msg(philo, YELLOW, "has taken a fork");
  print_msg(philo, YELLOW, "has taken a fork");
  print_msg(philo, GREEN, "is eating");
  pthread_mutex_lock(&philo->check_meal);
  philo->last_meal = get_current_time();
  // printf("-------> start: %zu\n", philo->data->start_time);
  pthread_mutex_unlock(&philo->check_meal);
  ft_wait(philo->data->time_to_eat);
  // printf("%safter eating...%s\n", RED, NC);
  pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
  pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);

  // pthread_mutex_lock(&philo->is_eating);
  philo->eat_count++;
  // pthread_mutex_unlock(&philo->is_eating);
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
    pthread_mutex_destroy(&philos[i].is_eating);
    pthread_mutex_destroy(&philos[i].check_meal);
    i++;
  }
  pthread_mutex_destroy(&data->dead_mutex);
  pthread_mutex_destroy(&data->print);
  pthread_mutex_destroy(&data->finished_m);

  free(forks);
  free(philos);
  // printf("all forks have been destroyed successfully\n");
}

void *philo_routine(void *philos)
{
  philo_t *philo;

  // philo = (philo_t * )philos;
  philo = (philo_t *) philos;
  if(philo->id % 2 == 0)
    usleep(15000);
    // ft_wait(philo->data->times_to_eat);
  while (1)
  { 
    pthread_mutex_lock(&philo->data->dead_mutex);
    if(philo->data->is_dead)
    {
      pthread_mutex_unlock(&philo->data->dead_mutex);
      break;
    }
    pthread_mutex_unlock(&philo->data->dead_mutex);
    if(philo->data->all_philos_ate == 1)
      break;
    ft_eat(philo);
    ft_sleep(philo);
    ft_think(philo);
    usleep(100);
  }
  return NULL;
}

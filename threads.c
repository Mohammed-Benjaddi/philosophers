#include "philo.h"

void start_program(data_t *data)
{
  int i;

  i = -1;
  while(++i < data->n_philos)
    pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
  while(!data->is_dead)
    check_dead_philo(data);
}

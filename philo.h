#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct philo_s
{
  int id;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int time_to_think;
  int times_to_eat;
  pthread_t thread;
} philo_t;

typedef struct data_s
{
  int n_philos;
  philo_t philos;
} data_t;

void ft_error();
int ft_atoi(char *str);
int init_vars(char **args, data_t *data);

#endif
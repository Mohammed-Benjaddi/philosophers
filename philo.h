#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_PHILOS 200
#define MAX_FORKS 200

typedef struct philo_s
{
  int id;
  pthread_t thread;
  int left_fork;
  int right_fork;
} philo_t;

typedef struct data_s
{
  int n_philos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int times_to_eat;
  philo_t *philos;
  pthread_mutex_t *forks;
} data_t;

void ft_error(char *str);
int ft_atoi(char *str);
int init_vars(char **args, data_t *data);
int init_philos(data_t *data);
int init_mutex(data_t *data);
void *philo_routine(void *data);

#endif
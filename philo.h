#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOS 200
#define MAX_FORKS 200

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"
# define GREEN	"\x1b[32m"
# define CYAN	"\x1b[36m"
# define RED	"\x1b[31m"
# define BLUE	"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define WHITE	"\x1b[37m"


typedef struct data_s data_t;
typedef struct philo_s
{
  int id;
  int current_time;
  pthread_t thread;
  int left_fork;
  int right_fork;
  int eat_count;
  int deadlock;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int times_to_eat;
  int last_meal;
  pthread_mutex_t is_eating;
  pthread_mutex_t check_meal;
  data_t *data;
} philo_t;

typedef struct data_s
{
  int n_philos;
  philo_t *philos;
  pthread_mutex_t *forks;
  pthread_mutex_t print;
  pthread_mutex_t dead_mutex;
  int is_dead;
} data_t;

void ft_error(char *str);
int ft_atoi(char *str);
int init_vars(char **args, data_t *data);
int init_philos(data_t *data, char **av);
int init_mutex(data_t *data);
void *philo_routine(void *data);
int get_current_time();
void ft_wait(int ms);
void destroy_all_forks(pthread_mutex_t *forks, int size);

void ft_think(philo_t *philo);
void ft_sleep(philo_t *philo);
void ft_eat(philo_t *phi);

void *philo_routine(void *data);
void print_msg(philo_t *philo, int flag);
// void check_is_dead(data_t *data);
int check_dead_philo(data_t *data);

#endif

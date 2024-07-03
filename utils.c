#include "philo.h"

void ft_error(char *msg)
{
  printf("%sError: %s%s\n", RED, msg, NC);
}

int get_current_time()
{
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void ft_wait(int ms)
{
  (void) ms;
  int start;

  start = get_current_time();
  while (get_current_time() - start < ms)
    usleep(250);
}

int ft_atoi(char *str)
{
  int result;
  int sign;
  int i;

  result = 0;
  sign = 1;
  i = 0;
  if(!str)
    return 0;
  while((str[i] >= 9 && str[i]<= 13) || str[i] == 32)
    i++;
  if(str[i] == '+' || str[i] == '-')
  {
    if(str[i] == '-')
      sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9')
  {
    result = (result * 10) + (str[i] - '0');
    i++;
  }
  return (result * sign);
}


int print_msg(philo_t *philo, int flag)
{
  pthread_mutex_lock(&philo->data->someone_died_m);
  if(!philo->data->someone_died)
  {
    pthread_mutex_lock(&philo->data->print);
    // pthread_mutex_lock(&philo->data->dead_mutex);
    pthread_mutex_lock(&philo->data->is_dead_m);
    if (philo->data->is_dead)
    {
      philo->data->someone_died = 1;
      printf("%s%d %d died%s\n", RED, get_current_time() - philo->current_time, philo->id, NC);
      pthread_mutex_unlock(&philo->data->print);
      // pthread_mutex_unlock(&philo->data->dead_mutex);
      // exit(0);
      return -1;
    }
    pthread_mutex_unlock(&philo->data->is_dead_m);
    // pthread_mutex_unlock(&philo->data->dead_mutex);
    if (flag == 1)
      printf("%s%d %d is eating%s\n", GREEN, get_current_time() - philo->current_time, philo->id, NC);
    else if (flag == 2)
      printf("%s%d %d is sleeping%s\n", CYAN, get_current_time() - philo->current_time, philo->id, NC);
    else if (flag == 3)
      printf("%s%d %d is thinking%s\n", MAGENTA, get_current_time() - philo->current_time, philo->id, NC);
    else if (flag == 4)
      printf("%s%d %d has taken a fork%s\n", YELLOW, get_current_time() - philo->current_time, philo->id, NC);
    else if (flag == 5)
      printf("%s%d %d has taken a fork%s\n", YELLOW, get_current_time() - philo->current_time, philo->id, NC);
    else if (flag == 10)
      printf("%s%d eating count: %d%s\n", RED, philo->id, philo->eat_count, NC);
    else if (flag == 25)
      printf("%s%d all philos ate%s\n", YELLOW, get_current_time() - philo->current_time, NC);
    
    pthread_mutex_unlock(&philo->data->print);
  }
  else
    return -1;
    // exit(1);
  pthread_mutex_unlock(&philo->data->someone_died_m);
  return 1;
}

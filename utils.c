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
  // printf("===> ms: %d\n", ms);
  while (get_current_time() - start < ms)
  {
    // printf("------->\n");
    usleep(200);
  }
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

void print_msg(philo_t *philo, char *color, char *description)
{
  // printf("--> %d\n", flag);
  pthread_mutex_lock(&philo->data->dead_mutex);

  // pthread_mutex_lock(&philo->data->finished_m);
  if(!philo->data->is_dead)
  {
    pthread_mutex_lock(&philo->data->print);
    printf("%s%lld %d %s%s\n", color, get_current_time() - philo->data->start_time, philo->id, description, NC);
    pthread_mutex_unlock(&philo->data->print);
  }
  // pthread_mutex_unlock(&philo->data->finished_m);
  pthread_mutex_unlock(&philo->data->dead_mutex);
}

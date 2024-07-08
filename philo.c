#include "philo.h"

int isValidNumber(char *nbr)
{
  int i;

  i = 0;
  while (nbr[i])
  {
    if(!(nbr[i] >= '0' && nbr[i] <= '9'))
      return 0;
    i++;
  }
  return 1;
}

int parsing(char **args)
{
  int i;

  i = 0;
  while (args[i])
  {
    if(!isValidNumber(args[i]))
      return (0);
    i++;
  }
  return 1;
}

void ft_free(void **arr)
{
  int i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);
    i++;
  }
  free(arr);
}

// void check_leaks()
// {
//   system("leaks -q philo");
// }

int main(int ac, char **av)
{
  // atexit(check_leaks);
  data_t *data;

  data = malloc(sizeof(data_t));

  if(ac != 5 && ac != 6)
    return (1);
  if(!parsing(av + 1))
    return (ft_error("Arguments are not valid"), 1);
  if(!init_program(av + 1, data))
    return ft_error("Something went wrong!"), 1;
  // printf("time to die: %d\n", data->time_to_die);
  // printf("time to eat: %d\n", data->time_to_eat);
  // printf("time to sleep: %d\n", data->time_to_sleep);
  start_program(data);
  destroy_all_forks(data, data->n_philos);
  free(data);
  return (1);
}

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
      return 0;
    i++;
  }
  return 1;
}

int main(int ac, char **av)
{
  data_t *data;

  data = malloc(sizeof(data_t));

  if(ac != 5 && ac != 6)
    return (ft_error("Something went wrong"), 1);
  if(!parsing(av + 1))
    return (ft_error("Something went wrong"), 1);
  if(!init_vars(av + 1, data))
    return (ft_error("Something went wrong"), 1);
}

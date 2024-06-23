#include "philo.h"

int isValidNumber(char *nbr)
{
  int i;

  i = 0;
  // printf("nbr: %s\n", nbr);
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
  data_t data;
  if(ac != 5 && ac != 6)
    ft_error();
  printf("ac ---> %d\n", ac);
  if(!parsing(av + 1))
  {
    ft_error();
    return 0;
  }
  if(!init_vars(av + 1, &data))
  {
    ft_error();
    return 0;
  }

  printf("------> correct arguments\n");

}

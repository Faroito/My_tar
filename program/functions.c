/*
** functions.c for functions in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 16:46:20 2017 Timothée Couble
** Last update Sun Mar  5 19:01:37 2017 Timothée Couble
*/

#include "my.h"

void    error(char *msg)
{
  write(2, msg, strlen(msg));
  exit(84);
}

void    my_str_cpy(char *str1, char *str2, int n)
{
  int   i;

  i = 0;
  while (str2[i] != '\0' && i < n)
    {
      str1[i] = str2[i];
      i += 1;
    }
  while (i < n)
    str1[i++] = 0;
}

int	my_strn_cpy(char *str1, char *str2, int i, int max)
{
  int	n;

  n = 0;
  while (str2[i] != '\0' && n < max)
    {
      str1[n] = str2[i];
      i += 1;
      n += 1;
    }
  str1[n] = 0;
  return (n);
}

void    my_put_in_str(unsigned int nbr, char *str, int max)
{
  int   i;
  int   mod;

  mod = 0;
  i = max - 2;
  while (i >= 0)
    {
      str[i] = ((nbr % my_power_rec(10, mod + 1))
		/ my_power_rec(10, mod) + '0');
      i -= 1;
      mod += 1;
    }
  str[max - 1] = 0;
}

void    file_exist(int ac, char **av, char *flags)
{
  int   i;

  if (flags[0] == '0')
    i = 2;
  else
    i = 3;
  while (i < ac)
    {
      if (access(av[i], F_OK) == -1)
        {
          write(2, av[i], strlen(av[i]));
          error(": file doesn\'t exist\n");
        }
      i += 1;
    }
}

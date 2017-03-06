/*
** change_base.c for change_base in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Mar  5 16:38:43 2017 Timothée Couble
** Last update Sun Mar  5 22:39:10 2017 Timothée Couble
*/

#include "my.h"

int	my_power_rec(int nb, int p)
{
  if (p == 0)
    nb = 1;
  else if (p < 0)
    nb = 0;
  else if (p > 1)
    nb = nb * my_power_rec(nb, p - 1);
  return (nb);
}

long long      my_get_decimal(char *str)
{
  unsigned long long    octal;
  long long             decimal;
  int   i;

  octal = 0;
  i = 0;
  while (str[i] != '\0')
    {
      octal *= 10;
      octal += str[i] - '0';
      i += 1;
    }
  decimal = 0;
  i = 0;
  while (octal != 0)
    {
      decimal += (octal % 10) * my_power_rec(8, i);
      i += 1;
      octal /= 10;
    }
  return (decimal);
}

int     my_get_octal(unsigned int nb)
{
  int   i;
  unsigned int  result;

  i = 0;
  result = 0;
  while (nb >= 8)
    {
      result += (nb % 8) * my_power_rec(10, i);
      i += 1;
      nb = nb / 8;
    }
  result += (nb % 8) * my_power_rec(10, i);
  return (result);
}

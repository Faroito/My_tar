/*
** read_symlink.c for read_symlink in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Mar  5 22:56:25 2017 Timothée Couble
** Last update Sun Mar  5 23:25:38 2017 Timothée Couble
*/

#include "my.h"

void	fill_zero(char *str, int i, int max)
{
  while (i < max)
    {
      str[i] = 0;
      i += 1;
    }
}

void	read_symlink(t_tar *tar, char *name)
{
  int	i;

  i = readlink(name, tar->linkname, sizeof(tar->linkname));
  if (i == -1)
    error("Error readlink\n");
  fill_zero(tar->linkname, i, 100);
  my_put_in_str(0, tar->size, sizeof(tar->size));
  my_put_in_str(777, tar->mode, sizeof(tar->mode));
}

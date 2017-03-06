/*
** end_file.c for end_file in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 18:07:14 2017 Timothée Couble
** Last update Sun Mar  5 17:23:56 2017 Timothée Couble
*/

#include "my.h"

void	end_file(int fd, int nb_block)
{
  int	max;
  int	i;
  char	buffer[512];

  i = 0;
  while (i < 512)
    buffer[i++] = 0;
  i = 0;
  max = 0;
  while ((max * 20) - nb_block < 1)
    max += 1;
  while (i < (max * 20) - nb_block)
    {
      write(fd, buffer, 512);
      i += 1;
    }
}

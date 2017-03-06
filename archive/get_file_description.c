/*
** get_file_description.c for get_file_description in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 17:08:16 2017 Timothée Couble
** Last update Sun Mar  5 17:45:51 2017 Timothée Couble
*/

#include "my.h"

void	access_mode(char *str, struct stat sb)
{
  int	size;
  int	i;
  int	*mode;

  if ((mode = malloc(sizeof(int) * 10)) == NULL)
    error("Error malloc\n");
  size = 256;
  i = 0;
  while (size > 0)
    {
      if ((sb.st_mode & size) != 0)
        mode[i++] = 1;
      else
        mode[i++] = 0;
      size /= 2;
    }
  mode[i] = 0;
  i = 0;
  while (i < 4)
    str[i++] = '0';
  str[4] = mode[0] * 4 + mode[1] * 2 + mode[2] + '0';
  str[5] = mode[3] * 4 + mode[4] * 2 + mode[5] + '0';
  str[6] = mode[6] * 4 + mode[7] * 2 + mode[8] + '0';
  str[7] = 0;
  free(mode);
}

void	my_get_mtime(int nb, char *str)
{
  int	i;

  i = 10;
  while (i > 0)
    {
      str[i] = nb % 8 + '0';
      i -= 1;
      nb = nb / 8;
    }
  str[i] = nb % 8 + '0';
  str[11] = 0;
}

char	testing_file(mode_t st_mode, char *name)
{
  int	i;
  int	file_test[7];
  char	buf[1];

  file_test[0] = S_ISREG(st_mode);
  if (readlink(name, buf, 1) > 0)
    return ('2');
  file_test[1] = -1;
  file_test[2] = -1;
  file_test[3] = S_ISCHR(st_mode);
  file_test[4] = S_ISBLK(st_mode);
  file_test[5] = S_ISDIR(st_mode);
  file_test[6] = S_ISFIFO(st_mode);
  i = 0;
  while (i < 7)
    {
      if (file_test[i] == 1)
        return (i + '0');
      i += 1;
    }
  return ('7');
}

int	result_ascii(char *str)
{
  int	i;
  int	nbr;

  i = 0;
  nbr = 0;
  while (str[i] != '\0')
    {
      nbr += str[i];
      i += 1;
    }
  return (nbr);
}

int	add_all_struct(t_tar *tar)
{
  int	nbr;

  nbr = 0;
  nbr = 8 * 32 + '0' * 2 + tar->typeflag;
  nbr += result_ascii(tar->name);
  nbr += result_ascii(tar->mode);
  nbr += result_ascii(tar->uid);
  nbr += result_ascii(tar->gid);
  nbr += result_ascii(tar->size);
  nbr += result_ascii(tar->mtime);
  nbr += result_ascii(tar->linkname);
  nbr += result_ascii(tar->magic);
  nbr += result_ascii(tar->uname);
  nbr += result_ascii(tar->gname);
  nbr += result_ascii(tar->devmajor);
  nbr += result_ascii(tar->devminor);
  return (my_get_octal(nbr));
}

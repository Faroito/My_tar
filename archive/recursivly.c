/*
** recursivly.c for recursivly in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 17:28:24 2017 Timothée Couble
** Last update Sun Mar  5 22:35:40 2017 Timothée Couble
*/

#include "my.h"

int	my_str_compact(char *str, char *name, int i)
{
  int	n;

  n = 0;
  while (name[n] != '\0')
    {
      str[i] = name[n];
      n += 1;
      i += 1;
    }
  str[i] = 0;
  return (i);
}

char	*change_name(char *name, char *name_dir)
{
  char	*new_name;
  int	i;

  if (name[0] == '.' && name[1] == 0)
    return (NULL);
  if (name[0] == '.' && name[1] == '.' && name[2] == 0)
    return (NULL);
  if ((new_name = malloc(strlen(name) + strlen(name_dir) + 2)) == NULL)
    error("Error malloc\n");
  i = my_str_compact(new_name, name_dir, 0);
  if (new_name[i - 1] != '/')
    {
      new_name[i] = '/';
      i += 1;
      new_name[i] = 0;
    }
  my_str_compact(new_name, name, i);
  if (access(new_name, R_OK) == -1)
    {
      write(2, new_name, strlen(new_name));
      free(new_name);
      error(": can't read file\n");
    }
  return (new_name);
}

int		write_repository(int fd_dest, char *name_dir, char *flags)
{
  DIR           *dirent;
  struct dirent *dir;
  char		*name_file;
  int		block_nb;

  block_nb = 0;
  if ((dirent = opendir(name_dir)) == NULL)
    return (-1);
  while ((dir = readdir(dirent)) != NULL)
    {
      if ((name_file = change_name(dir->d_name, name_dir)) != NULL)
	{
	  block_nb += write_tar(fd_dest, name_file, flags);
	  free(name_file);
	}
    }
  closedir(dirent);
  return (block_nb);
}
